#include <ncurses.h>
#include <cstring>
#include "../../semaphore/src/fulecoSimpleSemaphore.h"
#include <thread>

#ifndef TERMINAL_GAME_INPUT
#define TERMINAL_GAME_INPUT

namespace fulio {
#define SEM_NAME "INPUT_LOCK"
#define ACTION_SIZE 8

  enum inTypes {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    INTERACT,
    PAUSE,
    QUIT,
    ANY
  };

  class inputStructure {
    private:
    bool inputs[8] = {false};
    public:
    void setInput(int index);

    void setInput(inTypes index);

    bool getInput(int index);

    bool getInput(inTypes index);

    void reset();

  };

  class InBuff {
    private:
    std::thread t;
    bool active = false;
    inputStructure input;

    void inputLoop();

    public:
    void start();

    void stop();

    inputStructure getInputs();
  };
}

#endif
