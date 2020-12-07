//
// Created by Gabriel Souza on 07/12/20.
//

#ifndef TERMINAL_GAME_GAME_H
#define TERMINAL_GAME_GAME_H
#define FRAME_TIME_IN_MILLIS 10

#define MONSTER_EASY Status(2, 1, 5, 0, 1)
#define MONSTER_MEDIUM Status(5, 3, 10, 3, 1.2)
#define MONSTER_HARD Status(10, 6, 20, 5, 1.5)

#define DEFAULT_PLAYER Status(6, 1, 20, 3, 1.5)

#include <thread>
#include "src/map.h"
#include "src/item.h"
#include "src/character.h"
#include "io/src/io.h"

class Game {
  private:
  int score;
  bool isRunning;
  Map *map{};
  Character *player{};
  std::vector<Character> *monsters{};
  std::vector<Item> *items{};
  fulio::InBuff *input;
  std::thread threads[3];

  void shouldFinish(fulio::inputStructure frameInputs);

  void runOutput();

  void runActions();

  public:
  Game();

  void run();
  void cleanup();
};


#endif //TERMINAL_GAME_GAME_H
