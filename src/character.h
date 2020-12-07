#include <climits>
//
// Created by Gabriel Souza on 23/10/20.
//

#include "item.h"
#include "map.h"
#include "position.h"

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
  int attack{};
  int defense{};
  int mp{};
  float specialAbilityMultiplier{};
  int hp{};

  Status(int _attack, int _defense, int _hp, int _mp, float _specialAbilityMultiplier);
};

class Character {
  private:

  bool canMove(::Position new_position, Map map);

  public:
  Status status;

  void move(int direction, const Map &map);

  void useItem(const Item &item);

  Position position;

  Character(Position _position, Status _status);

};


#endif //TERMINAL_GAME_PLAYER_H
