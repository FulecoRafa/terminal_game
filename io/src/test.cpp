#include <cstdio>
#include "output.h"

int main (void) {
  fulio::Outbuff gamescr;
  gamescr.startLib();
  gamescr.drawMenu();
  gamescr.drawDinamic();
  getch();
  gamescr.setMsg("First Message");
  getch();
  gamescr.setMsg("You found an enemy. Fear the power of Chrome, The Ram Killer!");
  getch();
  gamescr.endLib();

  return 0;
}
