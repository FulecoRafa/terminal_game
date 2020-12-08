#include <thread>
#include <chrono>
#include "src/map.h"
#include "src/item.h"
#include "src/character.h"
#include "src/position.h"
#include "io/src/io.h"

#define FRAME_TIME_IN_MILLIS 60
#define CHARACTER_SEM "CHARACTER_LOCK"

#define MONSTER_EASY Status(2, 1, 5, 0, 1)
#define MONSTER_MEDIUM Status(5, 3, 10, 3, 1.2)
#define MONSTER_HARD Status(10, 6, 20, 5, 1.5)

#define THREAD_COUNT 4

#define DEFAULT_PLAYER Status(6, 1, 20, 3, 1.5)

void runActions(Map *map, Character *player, std::vector<Character> *monsters, std::vector<Item> *items,
                fulio::InBuff *input, bool *isRunning, std::string *message, int *score) {
  bool action;
  int fightingMonster = -1;
  while (true) {
    fulio::inputStructure activeInputs = input->getInputs();
    if (activeInputs.getInput(fulio::QUIT)) break;
    if (fightingMonster >= 0) {
      if (activeInputs.getInput(fulio::INTERACT)) {
        fulss::lock(CHARACTER_SEM);
        player->fight(monsters->at(fightingMonster), message, score);
        monsters->erase(monsters->begin() + fightingMonster);
        fightingMonster = -1;
        fulss::unlock(CHARACTER_SEM);
      }
      continue;
    }
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
      fulss::lock(CHARACTER_SEM);
      if (player->isEnemyInRange(&monsters->at(i))) {
        fightingMonster = i;
        *message = "FIGHT!!! (press I)";
      }
      fulss::unlock(CHARACTER_SEM);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_TIME_IN_MILLIS));
  }
  *isRunning = false;
}

void
runOutput(Map *map, Character *player, std::vector<Character> *monsters, const std::vector<Item> *items,
          const bool *isRunning, std::string *message, int *score) {
  fulio::Outbuff screen{};
  screen.startLib();
  screen.drawMenu();
  while (*isRunning) {
    screen.drawDinamic(*map, *player, *score, *monsters, *items);
    std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_TIME_IN_MILLIS));
    screen.setMsg(*message);
  }
  screen.endLib();
};

int main() {
  // Initializing game objects
  bool isRunning = true;
  int score = 0;
  fulss::create_mutex(CHARACTER_SEM);
  Map map = Map();
  std::string message;
  Character player = Character(Position(MAP_SIZE_Y - 2, MAP_SIZE_X / 2), DEFAULT_PLAYER);
  std::vector<Character> monsters = {
    Character(Position(3, 7), MONSTER_EASY),
    Character(Position(9, MAP_SIZE_X - 12), MONSTER_EASY),
    Character(Position(MAP_SIZE_Y / 2, MAP_SIZE_X / 2), MONSTER_EASY),
  };
  std::vector<Item> items = {
    Item(Position(7, MAP_SIZE_X - 31), ATK_POWER, 4, "Long Sword")
  };
  map.readMap(MAP_1);

  // i/o setup

  std::thread threads[2];
  fulio::InBuff input;
  input.start();

  // Output
  threads[0] = std::thread(runOutput, &map, &player, &monsters, &items, &isRunning, &message, &score);
  threads[1] = std::thread(runActions, &map, &player, &monsters, &items, &input, &isRunning, &message, &score);

  // clean up
  for (auto &thread : threads) {
    thread.join();
  }
  input.stop();

  return 0;
}
