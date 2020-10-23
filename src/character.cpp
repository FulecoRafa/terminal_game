//
// Created by Gabriel Souza on 23/10/20.
//

#include "character.h"

bool Character::canMove(::Position new_position, Map map) {
  // @TODO treat collision with other characters (players/monsters)
  switch (map.getTerrainInPosition(new_position)) {
    case EMPTY:
      return true;
    default:
      return false;
  }
}

void Character::move(int direction, Map map) {
  ::Position newPosition{};
  switch (direction) {
    case UP: {
      newPosition.x = this->position.x;
      newPosition.y = this->position.y - 1;
      if (canMove(newPosition, map)) this->position = newPosition;
      return;
    }
    case DOWN: {
      newPosition.x = this->position.x;
      newPosition.y = this->position.y + 1;
      if (canMove(newPosition, map)) this->position = newPosition;
      return;
    }
    case LEFT: {
      newPosition.x = this->position.x - 1;
      newPosition.y = this->position.y;
      if (canMove(newPosition, map)) this->position = newPosition;
      return;
    }
    case RIGHT: {
      newPosition.x = this->position.x + 1;
      newPosition.y = this->position.y;
      if (canMove(newPosition, map)) this->position = newPosition;
      return;
    }
    default: {
      return;
    }
  }
}


