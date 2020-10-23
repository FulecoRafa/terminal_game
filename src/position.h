//
// Created by Gabriel Souza on 23/10/20.
//

#ifndef TERMINAL_GAME_POSITION_H
#define TERMINAL_GAME_POSITION_H

// This class is just to avoid circular dependency

class Position {
  public:
  int x{};
  int y{};

  explicit Position(int y, int x);
};



#endif //TERMINAL_GAME_POSITION_H
