//
// Created by Gabriel Souza on 23/10/20.
//

#include <vector>
#include "map.h"
#include "character.h"

#ifndef TERMINAL_GAME_OUTPUT_H
#define TERMINAL_GAME_OUTPUT_H


class Output {
  public:
  static void printCurrentFrame(const Map& map, Character player, const std::vector<Character>& monsters, const std::vector<Item>& items);
};


#endif //TERMINAL_GAME_OUTPUT_H
