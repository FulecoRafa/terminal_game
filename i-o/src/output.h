#include <ncurses.h>
#include <locale.h>
#include <string>

#ifndef TERMINAL_GAME_OUTPUT
#define TERMIANL_GAME_OUTPUT

void drawBox(int y, int x, int height, int width);
bool startLib();
void drawMenu();
void drawDinamic();
void endLib();

#endif
