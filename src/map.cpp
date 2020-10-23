//
// Created by Gabriel Souza on 23/10/20.
//

#include "map.h"

char Map::getTerrainInPosition(Position position) {
  if (position.x < 0 || position.x >= MAP_SIZE_X || position.y < 0 || position.y >= MAP_SIZE_Y) return OUTSIDE;
  return terrain[position.x][position.y];
}
