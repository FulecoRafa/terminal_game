//
// Created by Gabriel Souza on 23/10/20.
//

#include "map.h"

unsigned char Map::getTerrainInPosition(Position position) {
  if (position.x < 0 || position.x >= MAP_SIZE_X || position.y < 0 || position.y >= MAP_SIZE_Y) return OUTSIDE;
  return terrain[position.y][position.x];
}

void createTerrainMutexes(std::vector<std::string> terrain) {
  for (int i = 0; i < MAP_SIZE_Y; i++) {
    for (int j = 0; j < MAP_SIZE_X; j++) {
      if (terrain[i][j] == '.') {
        std::string mutexName = "MTX_" + std::to_string(i) + "_" + std::to_string(j);
        fulss::create_mutex(mutexName);
      }
    }
  }
}

void Map::readMap(MapTypes type) {
  std::vector<std::string> map;
  std::string line;
  std::ifstream mapFile("src/maps/map_1.txt");
  if (mapFile.is_open()) {
    while (std::getline(mapFile, line)) {
      map.push_back(line);
    }
    mapFile.close();
  } else {
    printf("Map file not found");
    exit(1);
  }
  terrain = map;
  createTerrainMutexes(terrain);
}


