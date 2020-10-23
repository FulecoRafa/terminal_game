//
// Created by Gabriel Souza on 23/10/20.
//

#ifndef TERMINAL_GAME_MAP_H
#define TERMINAL_GAME_MAP_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include "position.h"


#define MAP_SIZE_X 86
#define MAP_SIZE_Y 17

enum TerrainType {
  EMPTY = ' ',
  WALL = '#',
  OUTSIDE = '-',
};

enum MapTypes {
  MAP_1 = 1
};

class Map {
  public:
  std::vector<std::string> terrain;
  unsigned char getTerrainInPosition(Position position);
  void readMap(MapTypes type);
};


#endif //TERMINAL_GAME_MAP_H
