#include "output.h"

namespace fulio {

#define MAX_MAP 1224
#define MAX_MSG 175

  void drawBox(int y, int x, int height, int width) {

    // Create box borders
    mvvline(y, x, '|', height);
    mvvline(y, width + x, '|', height);
    mvhline(y, x, '-', width);
    mvhline(height + y, x, '-', width);

    // Create box vertices
    mvaddch(y, x, '/');
    mvaddch(y, x + width, '\\');
    mvaddch(y + height, x, '\\');
    mvaddch(y + height, x + width, '/');

  }

  bool Outbuff::startLib() {
    initscr();
    //raw();
    //noecho();
    clear();
    //curs_set(0);

    // Check window size
    int my, mx;
    getmaxyx(stdscr, my, mx);
    if (!(my >= 26 && mx >= 120)) {
      endwin();
      printf("Terminal window must be at least 26 columns high and 120 rows wide.\n\
Your terminal is [%d,%d]\n\
Please resize your terminal and run game again...\n", my, mx);
      return false;
    }

    wresize(stdscr, 40, 170);

    // Color setup
    start_color();
    use_default_colors();
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_YELLOW, -1);
    init_pair(3, COLOR_GREEN, -1);
    init_pair(4, COLOR_BLUE, -1);

    // Window setup
    msgwin = newwin(5, 35, 16, 77);
    mapwin = newwin(19, 68, 3, 3);

    // Final Setup

    return true;
  }

  void Outbuff::drawMenu() {
    // Creating boxes
    attron(A_DIM);
    drawBox(2, 2, 20, 70); // Map
    drawBox(2, 74, 20, 40); // Status
    drawBox(4, 76, 2, 36); // Health
    drawBox(8, 76, 2, 36); // Mana
    drawBox(15, 76, 6, 36); // Messages
    attroff(A_DIM);

    // Box titles
    // Map
    mvprintw(2, 8, "Score: ");
    // Status
    mvprintw(2, 80, "Status: ");
    // Health
    mvprintw(4, 80, "Health: ");
    // Mana
    mvprintw(8, 80, "Mana: ");
    // Messages
    mvprintw(15, 80, "Messages: ");


    // Help
    attron(COLOR_PAIR(2));
    move(24, 15);
    printw("w: Move Up       ");
    move(26, 2);
    printw("a: Move Left      ");
    move(26, 15);
    printw("s: Move Down       ");
    move(26, 30);
    printw("d: Move Right       ");
    move(24, 45);
    printw("i: Interact");
    move(24, 65);
    printw("p: Pause");
    move(25, 65);
    printw("q: Quit");

  }

  void Outbuff::drawDynamic(Map &map, Character &player, int &score, std::vector<Character *> &monsters,
                            std::vector<Item> items) {
    // Access critical region to get info for display
    // CRITICAL REGION START
    int lscore = score;
    int lhealth = player.status.hp;
    int lmana = player.status.mp;
    int atk = player.status.attack, deff = player.status.defense;
    std::vector<std::string> aux_terrain = map.terrain;
    //CRITICAL REGION END

    // Print numbers to titles
    attron(COLOR_PAIR(3));
    mvprintw(2, 15, "%03d", lscore); // lscore
    mvprintw(4, 88, "%03d", lhealth); // lhealth
    mvprintw(8, 86, "%03d", lmana); // lmana

    // lhealth Bar
    int starty = 5, startx = 78;
    move(starty, startx);
    for (int i = 0; i < 4; i++) {
      attron(COLOR_PAIR(i + 1));
      for (int j = 0; j < 340; j += 10) {
        if (340 * i + j < lhealth) addch('|');
        else move(starty, startx + 1);
        startx++;
      }
      startx = 78;
      move(starty, startx);
    }
    attroff(COLOR_PAIR(3));

    // lmana Bar
    starty = 9, startx = 78;
    move(starty, startx);
    for (int i = 0; i < 4; i++) {
      attron(COLOR_PAIR(i + 1));
      for (int j = 0; j < 340; j += 10) {
        if (340 * i + j < lmana) addch('|');
        else move(starty, startx + 1);
        startx++;
      }
      startx = 78;
      move(starty, startx);
    }
    attroff(COLOR_PAIR(3));

    //Attack and deffense
    attron(COLOR_PAIR(1));
    mvprintw(13, 78, "Attack: ");
    printw("%3d", atk);
    attron(COLOR_PAIR(4));
    printw("   Deffense: ");
    printw("%3d", deff);
    attroff(COLOR_PAIR(4));

    // Printing map
    wclear(mapwin);
    aux_terrain[player.position.y][player.position.x] = 'H';
    for (Character *monster : monsters) {
      if (monster->status.lvl == 1) aux_terrain[monster->position.y][monster->position.x] = '1';
      else if (monster->status.lvl == 2) aux_terrain[monster->position.y][monster->position.x] = '2';
      else if (monster->status.lvl == 3) aux_terrain[monster->position.y][monster->position.x] = '3';
    }
    for (const Item &item : items) {
      aux_terrain[item.position.y][item.position.x] = '*';
    }
    for (std::string line : aux_terrain) {
      wprintw(mapwin, "%s", line.c_str());
    }
    wrefresh(mapwin);

    refresh();

  }

  void Outbuff::setMsg(std::string newMsg) {
    if (newMsg.length() <= MAX_MSG) {
      wclear(msgwin);
      wprintw(msgwin, newMsg.c_str());
      wrefresh(msgwin);
    }
  }

  void Outbuff::endLib() {
    delwin(mapwin);
    delwin(msgwin);
    endwin();
  }
}
