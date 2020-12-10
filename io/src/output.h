#include <ncurses.h>
#include <string>
#include <vector>
#include "../../src/character.h"
#include "../../src/map.h"
#include "../../src/item.h"
#include "../../src/position.h"

#ifndef TERMINAL_GAME_OUTPUT
#define TERMINAL_GAME_OUTPUT

namespace fulio {
  void drawBox(int y, int x, int height, int width);

  class Outbuff {
    private:
    WINDOW *msgwin;
    WINDOW *mapwin;
    public:
    bool startLib();

    void drawMenu();

    void
    drawDynamic(Map &map, Character &player, int &score, std::vector<Character *> &monsters, std::vector<Item> items);

    void setMsg(std::string newMsg);

    void endLib();
  };
}

#endif
