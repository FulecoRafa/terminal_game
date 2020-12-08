//
// Created by Gabriel Souza on 23/10/20.
//

#include <climits>
#include <string>
#include <cmath>
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
  int xp = 0;

  Status(int _attack, int _defense, int _hp, int _mp, float _specialAbilityMultiplier);
};

class Character {
  private:

  bool canMove(::Position new_position, Map map, std::vector<Character> *otherCharacters, std::vector<Item> *items);

  Position calculateNewPosition(int direction) const;

  public:
  Status status;

  void move(int direction, const Map &map, std::vector<Character> *otherCharacters, std::vector<Item> *items);

  void useItem(const Item &item);

  void fight(Character enemy, std::string *message, int *score);

  Position position;

  static std::string getMoveMessage(int direction);

  Character(Position _position, Status _status);

  bool isEnemyInRange(Character *enemy);

  void lvlUp(std::string *message);
};


#endif //TERMINAL_GAME_PLAYER_H
