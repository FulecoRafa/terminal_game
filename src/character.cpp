//
// Created by Gabriel Souza on 23/10/20.
//

#include "character.h"

bool hasEntityInPosition(Position newPosition, Position entityPosition) {
  return newPosition.x == entityPosition.x && newPosition.y == entityPosition.y;
}

bool isOneCharacterInPosition(Position newPosition, const std::vector<Character *> &characters) {
  for (auto character: characters) {
    if (hasEntityInPosition(newPosition, character->position)) return true;
  }
  return false;
}

bool isOneItemInPosition(Position newPosition, const std::vector<Item> &items) {
  for (const auto &item: items) {
    if (hasEntityInPosition(newPosition, item.position)) return true;
  }
  return false;
}

Position Character::calculateNewPosition(int direction) const {
  Position newPosition = this->position;
  switch (direction) {
    case UP: {
      newPosition = Position(this->position.y - 1, this->position.x);
      break;
    }
    case DOWN: {
      newPosition = Position(this->position.y + 1, this->position.x);
      break;
    }
    case LEFT: {
      newPosition = Position(this->position.y, this->position.x - 1);
      break;
    }
    case RIGHT: {
      newPosition = Position(this->position.y, this->position.x + 1);
      break;
    }
  }
  return newPosition;
};

bool Character::isEnemyInRange(Character *enemy) {
  for (int i = 0; i < 4; i++) {
    Position nextPosition = this->calculateNewPosition(i);
    if (hasEntityInPosition(nextPosition, enemy->position)) return true;
  }
  return false;
}


bool
Character::canMove(::Position newPosition, Map map, std::vector<Character *> *otherCharacters,
                   std::vector<Item> *items) {
  // @TODO treat collision with other characters (players/monsters)
  unsigned char terrainType = map.getTerrainInPosition(newPosition);
  if (terrainType == EMPTY) {
    if (isOneCharacterInPosition(newPosition, *otherCharacters)) return false;
    if (isOneItemInPosition(newPosition, *items)) return false;
    return true;
  }
  return false;
}

void
Character::move(int direction, const Map &map, std::vector<Character *> *otherCharacters, std::vector<Item> *items) {
  Position newPosition = this->calculateNewPosition(direction);
  if (canMove(newPosition, map, otherCharacters, items)) this->position = newPosition;
}

void Character::moveEnemy(int direction, const Map &map, std::vector<Character *> *otherCharacters, std::vector<Item> *items,
                     Character *player) {
  Position newPosition = this->calculateNewPosition(direction);
  std::vector<Character> playerAux;
  playerAux.push_back(*player);
  if (canMove(newPosition, map, otherCharacters, items)) this->position = newPosition;
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

std::string Character::getMoveMessage(int direction) {
  switch (direction) {
    case UP:
      return "You moved up.";
    case LEFT:
      return "You moved left.";
    case DOWN:
      return "You moved down.";
    case RIGHT:
      return "You moved right.";
    default:
      return "";
  }
}

void Character::lvlUp(std::string *message) {
  if (status.xp >= 5) {
    status.hp += 10;
    status.mp += 5;
    status.attack += 1;
    status.defense += 1;
    status.xp = 0;
    *message = *message + "\n" + "You leveled up!";
  }
}

void Character::fight(Character *enemy, std::string *message, int *score) {
  int attackTimes = floor(enemy->status.hp / (status.attack - enemy->status.defense));
  int damage = (enemy->status.attack) * attackTimes;
  status.hp = status.hp - damage;
  if (status.hp < 0) {
    *message = "YOU DIED!!!";
    return;
  }
  *message = "You received 2 experience points!";
  status.xp += 2;
  *score += 10;
  this->lvlUp(message);
}

Status::Status(int _attack, int _defense, int _hp, int _mp, float _specialAbilityMultiplier) {
  attack = _attack;
  defense = _defense;
  mp = _mp;
  specialAbilityMultiplier = _specialAbilityMultiplier;
  hp = _hp;
}
