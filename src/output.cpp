//
// Created by Gabriel Souza on 23/10/20.
//

#include "output.h"

void Output::printCurrentFrame(const Map &map, Character player, const std::vector<Character> &monsters,
                               const std::vector<Item> &items) {
  std::vector<std::string> aux_terrain = map.terrain;
  aux_terrain[player.position.y][player.position.x] = 'P';
  for (Character monster : monsters) {
    aux_terrain[monster.position.y][monster.position.x] = 'M';
  }
  for (const Item &item : items) {
    aux_terrain[item.position.y][item.position.x] = 'I';
  }
  // ZONA CRITICA //
  for (int i = 0; i < MAP_SIZE_Y; i++) {
    for (int j = 0; j < MAP_SIZE_X; j++) {
      std::cout << aux_terrain[i][j];
    }
    std::cout << std::endl;
  }
  // FIM ZONA CRITICA //
}
