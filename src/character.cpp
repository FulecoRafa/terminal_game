//
// Created by Gabriel Souza on 23/10/20.
//

#include "character.h"

bool Character::canMove(::Position newPosition, Map map) {
  // @TODO treat collision with other characters (players/monsters)
  switch (map.getTerrainInPosition(newPosition)) {
    case EMPTY:
      return true;
    default:
      return false;
  }
}

void Character::move(int direction, const Map &map) {

  switch (direction) {
    case UP: {
      Position newPosition = Position(this->position.y - 1, this->position.x);
      if (canMove(newPosition, map)) this->position = newPosition;
      return;
    }
    case DOWN: {
      Position newPosition = Position(this->position.y + 1, this->position.x);
      if (canMove(newPosition, map)) this->position = newPosition;
      return;
    }
    case LEFT: {
      Position newPosition = Position(this->position.y, this->position.x - 1);
      if (canMove(newPosition, map)) this->position = newPosition;
      return;
    }
    case RIGHT: {
      Position newPosition = Position(this->position.y, this->position.x + 1);
      if (canMove(newPosition, map)) this->position = newPosition;
      return;
    }
    default: {
      return;
    }
  }
}

void Character::useItem(const Item &item) {
  switch (item.type) {
    case HEAL: {
      status.hp += item.value;
      return;
    }
    case ATK_POWER: {
      status.attack += item.value;
      return;
    }
    case DEF_POWER: {
      status.defense += item.value;
      return;
    }
    case MANA_HEAL: {
      status.mp += item.value;
      return;
    }
    default: {
      return;
    }
  }
}

Character::Character(Position _position, Status _status) : position(_position), status(_status) {
  status = _status;
  position = _position;
}

Status::Status(int _attack, int _defense, int _hp, int _mp, float _specialAbilityMultiplier) {
  attack = _attack;
  defense = _defense;
  mp = _mp;
  specialAbilityMultiplier = _specialAbilityMultiplier;
  hp = _hp;
}
