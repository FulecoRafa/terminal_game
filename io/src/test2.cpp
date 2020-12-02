#include <chrono>
#include <cstdio>
#include <ncurses.h>
#include "io.h"

int main (void) {
  initscr();
  raw();
  fulio::InBuff input;
  input.start();
  std::this_thread::sleep_for(std::chrono::seconds(3));
  printf("input stop\n");
  fulio::inputStructure activeInputs = input.getInputs();
  for (int i = 0; i < 8 ; i++ ) {
    printf("%c", activeInputs.getInput(i)?'1':'0');
  }
  input.stop();
}
