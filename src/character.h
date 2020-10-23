#include <climits>
//
// Created by Gabriel Souza on 23/10/20.
//

#include "map.h"

#ifndef TERMINAL_GAME_PLAYER_H
#define TERMINAL_GAME_PLAYER_H

enum MoveTypes {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

class Status {
  public:
  int attack;
  int defense;
  int hp;
  int mp;
  float specialAbilityMultiplier;
};

class Character {
  private:
  Position position;
  Status status;
  bool canMove(::Position new_position, Map map);

  public:
  void move(int direction, Map map);
};


#endif //TERMINAL_GAME_PLAYER_H
