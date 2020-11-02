#include <iostream>
#include <thread>
#include <chrono>
#include "src/fulecoSimpleSemaphore.h"
#include "src/map.h"
#include "src/item.h"
#include "src/character.h"
#include "src/output.h"
#include "src/position.h"

#define MONSTER_EASY Status(2, 1, 5, 0, 1)
#define MONSTER_MEDIUM Status(5, 3, 10, 3, 1.2)
#define MONSTER_HARD Status(10, 6, 20, 5, 1.5)

#define DEFAULT_PLAYER Status(6, 1, 20, 3, 1.5)

int main() {
  Map map = Map();
  Character player = Character(Position(MAP_SIZE_Y - 2, MAP_SIZE_X / 2), DEFAULT_PLAYER);
  std::vector<Character> monsters = {
    Character(Position(3, 7), MONSTER_EASY),
    Character(Position(9, MAP_SIZE_X - 12), MONSTER_EASY),
    Character(Position(MAP_SIZE_Y / 2, MAP_SIZE_X / 2), MONSTER_EASY),
  };
  std::vector<Item> items = {
    Item(Position(5, MAP_SIZE_X - 31), ATK_POWER, 4, "Long Sword")
  };
  map.readMap(MAP_1);

  for (int i = 0; i < 10; i++) {
    Output::printCurrentFrame(map, player, monsters, items);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    player.move(UP, map);
  }
  return 0;
}
