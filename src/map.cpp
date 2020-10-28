//
// Created by Gabriel Souza on 23/10/20.
//

#include "map.h"

unsigned char Map::getTerrainInPosition(Position position) {
  if (position.x < 0 || position.x >= MAP_SIZE_X || position.y < 0 || position.y >= MAP_SIZE_Y) return OUTSIDE;
  return terrain[position.y][position.x];
}

void Map::readMap(MapTypes type) {
  std::vector<std::string> map(MAP_SIZE_Y);
  int i = 0;
  std::string line;
  std::ifstream mapFile("../src/maps/map_1.txt");
  if (mapFile.is_open()) {
    while (getline(mapFile, map[i])) i++;
    mapFile.close();
  }
  terrain = map;
}

