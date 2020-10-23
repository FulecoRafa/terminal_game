//
// Created by Gabriel Souza on 23/10/20.
//

#include "item.h"

#include <utility>

Item::Item(Position _position, ItemType _type, int _value, std::string _name) : position(_position) {
  position = _position;
  name = std::move(_name);
  type = _type;
  value = _value;
}
