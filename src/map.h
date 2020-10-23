//
// Created by Gabriel Souza on 23/10/20.
//

#ifndef TERMINAL_GAME_MAP_H
#define TERMINAL_GAME_MAP_H

#define MAP_SIZE_X 200
#define MAP_SIZE_Y 100

class Position {
  public:
    int x;
    int y;
};

enum TerrainType {
  EMPTY = ' ',
  WALL = '#',
  OUTSIDE = '-',
};

class Map {
  private:
    char terrain[MAP_SIZE_X][MAP_SIZE_Y];

  public:
    char getTerrainInPosition(Position position);
};


#endif //TERMINAL_GAME_MAP_H
