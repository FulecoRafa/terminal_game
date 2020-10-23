//
// Created by Gabriel Souza on 23/10/20.
//

#ifndef TERMINAL_GAME_ITEM_H
#define TERMINAL_GAME_ITEM_H

#include <string>
#include "position.h"

enum ItemType {
  HEAL,
  ATK_POWER,
  DEF_POWER,
  MANA_HEAL
};

class Item {
  public:
  Item(Position _position, ItemType _type, int _value, std::string _name);

  std::string name;
  Position position;
  ItemType type;
  int value;
};


#endif //TERMINAL_GAME_ITEM_H
