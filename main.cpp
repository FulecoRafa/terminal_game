#include <thread>
#include <chrono>
#include "src/map.h"
#include "src/item.h"
#include "src/character.h"
#include "src/position.h"
#include "io/src/io.h"

#define FRAME_TIME_IN_MILLIS 100
#define CHARACTER_SEM "CHARACTER_LOCK"

#define MONSTER_EASY Status(2, 1, 5, 0, 1)
#define MONSTER_MEDIUM Status(5, 3, 10, 3, 1.2)
#define MONSTER_HARD Status(10, 6, 20, 5, 1.5)

#define THREAD_COUNT 13

#define DEFAULT_PLAYER Status(6, 1, 20, 3, 1.5)

void
runIA(Map *map, Character *monster, Character *player, std::vector<Character *> *otherMonsters,
      std::vector<Item> *items,
      bool *isRunning) {
  int direction = 0;
  int range = 1;
  bool isIncreasingRange = true;
  int roundsDead = 0;
  int path[4] = {UP, RIGHT, DOWN, LEFT};
  while (*isRunning) {

    if (monster->status.hp <= 0) roundsDead++;
    if (roundsDead == 30) {
      roundsDead = 0;
      monster->status.hp = 20;
    }
    if (!player->isEnemyInRange(monster)) {
      if (direction == 3) {
        if (range == 1) isIncreasingRange = true;
        if (range == 3) isIncreasingRange = false;
        if (isIncreasingRange) range = (range + 1) % 3;
        else range = (range - 1) % 3;
      }
      fulss::down(CHARACTER_SEM);
      for (int i = 0; i < range; i++) {
//        fulss::lock(CHARACTER_SEM);
        monster->moveEnemy(path[direction], *map, otherMonsters, items, player);
//        fulss::unlock(CHARACTER_SEM);
      }
      fulss::up(CHARACTER_SEM);
      direction = (direction + 1) % 4;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

  }
}

void runActions(Map *map, Character *player, std::vector<Character *> *monsters, std::vector<Item> *items,
                fulio::InBuff *input, bool *isRunning, std::string *message, int *score) {
  bool action;
  int fightingMonster = -1;
  fulss::down(CHARACTER_SEM);

  while (*isRunning) {

    fulio::inputStructure activeInputs = input->getInputs();

    if (activeInputs.getInput(fulio::QUIT)) break;
    if (fightingMonster >= 0) {
      if (activeInputs.getInput(fulio::INTERACT)) {
        player->fight(monsters->at(fightingMonster), message, score);
        monsters->at(fightingMonster)->status.hp = 0;
        fightingMonster = -1;
      }
    } else {
      for (int j = 0; j < 4; j++) { // move actions
        action = activeInputs.getInput(j);
        if (action) {
          fulss::lock(CHARACTER_SEM);
          player->move(j, *map, monsters, items);
          *message = Character::getMoveMessage(j);
          fulss::unlock(CHARACTER_SEM);
        }
      }
      for (int i = 0; i < monsters->size(); i++) {
        if (monsters->at(i)->status.hp <= 0) continue;
        fulss::lock(CHARACTER_SEM);
        if (player->isEnemyInRange(monsters->at(i))) {
          fightingMonster = i;
          *message = "FIGHT!!! (press I)";
        }
        fulss::unlock(CHARACTER_SEM);
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }
  fulss::up(CHARACTER_SEM);

  *isRunning = false;
}

void
runOutput(Map *map, Character *player, std::vector<Character *> *monsters, const std::vector<Item> *items,
          const bool *isRunning, std::string *message, int *score) {
  fulio::Outbuff screen{};
  screen.startLib();
  screen.drawMenu();
  std::vector<Character *> aliveMonsters;
  while (*isRunning) {
    for (auto monster: *monsters) if (monster->status.hp > 0) aliveMonsters.push_back(monster);
    screen.drawDynamic(*map, *player, *score, aliveMonsters, *items);
    std::this_thread::sleep_for(std::chrono::milliseconds(60));
    screen.setMsg(*message);
    aliveMonsters.clear();
  }
  screen.endLib();
};

int main() {
  // Initializing game objects
  bool isRunning = true;
  int score = 0;
  int monsters_thread = 2;
  fulss::create_semaphore(CHARACTER_SEM, 7);
  fulss::create_mutex(CHARACTER_SEM);
  Map map = Map();
  std::string message;
  Character player = Character(Position(MAP_SIZE_Y - 2, MAP_SIZE_X / 2), DEFAULT_PLAYER);
  std::vector<Character *> monsters = {
    new Character(Position(3, 7), MONSTER_EASY),
    new Character(Position(9, MAP_SIZE_X - 12), MONSTER_EASY),
    new Character(Position(15, 3), MONSTER_MEDIUM),
    new Character(Position(MAP_SIZE_Y / 2, MAP_SIZE_X / 2), MONSTER_EASY),
    new Character(Position(0, MAP_SIZE_X - 20), MONSTER_MEDIUM),
    new Character(Position(7, 7), MONSTER_EASY),
    new Character(Position(3, MAP_SIZE_X - 12), MONSTER_MEDIUM),
    new Character(Position(MAP_SIZE_Y - 4, MAP_SIZE_X - 12), MONSTER_EASY),
    new Character(Position(2, MAP_SIZE_X / 2 + 6), MONSTER_MEDIUM),
    new Character(Position(4, MAP_SIZE_X / 2), MONSTER_EASY),
    new Character(Position(MAP_SIZE_Y - 4, MAP_SIZE_X / 2 - 12), MONSTER_HARD),
  };
  std::vector<Item> items = {
//    Item(Position(7, MAP_SIZE_X - 31), ATK_POWER, 4, "Long Sword")
  };
  map.readMap(MAP_1);

  // i/o setup

  std::thread threads[THREAD_COUNT];
  fulio::InBuff input;
  input.start();

  // Output
  threads[0] = std::thread(runOutput, &map, &player, &monsters, &items, &isRunning, &message, &score);
  threads[1] = std::thread(runActions, &map, &player, &monsters, &items, &input, &isRunning, &message, &score);
  for (auto monster: monsters) {
    threads[monsters_thread] = std::thread(runIA, &map, monster, &player, &monsters, &items, &isRunning);
    monsters_thread++;
  }
  // clean up
  for (auto &thread : threads) {
    thread.join();
  }
  input.stop();

  return 0;
}
