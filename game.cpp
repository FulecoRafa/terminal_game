//
// Created by Gabriel Souza on 07/12/20.
//

#include "game.h"

void Game::shouldFinish(fulio::inputStructure frameInputs) {
  bool action = frameInputs.getInput(fulio::QUIT);
  if (action) {
    isRunning = false;
    cleanup();
  }
}

void Game::runOutput() {
  fulio::Outbuff screen{};
  screen.startLib();
  screen.drawMenu();
  while (isRunning) {
    screen.drawDinamic(*map, *player, score, *monsters, *items);
    std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_TIME_IN_MILLIS));
//    std::string message = "You walked up ";
//    screen.setMsg(message);
    score += 10;
  }
  screen.endLib();
}

void Game::runActions() {
  while (isRunning) {
    fulio::inputStructure frameInputs = this->input->getInputs();
    shouldFinish(frameInputs);
    for (int j = 0; j < 4; j++) { // move actions
      if (frameInputs.getInput(j)) this->player->move(j, *map);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_TIME_IN_MILLIS));
  }
}

Game::Game() {
  tscore = 0;
  Map _map = Map();
  Character _player = Character(Position(MAP_SIZE_Y - 2, MAP_SIZE_X / 2), DEFAULT_PLAYER);
  std::vector<Character> _monsters = {
    Character(Position(3, 7), MONSTER_EASY),
    Character(Position(9, MAP_SIZE_X - 12), MONSTER_EASY),
    Character(Position(MAP_SIZE_Y / 2, MAP_SIZE_X / 2), MONSTER_EASY),
  };
  std::vector<Item> _items = {
    Item(Position(5, MAP_SIZE_X - 31), ATK_POWER, 4, "Long Sword")
  };
  fulio::InBuff _input;
  input = &_input;
  map = &_map;
  player = &_player;
  monsters = &_monsters;
  items = &_items;
  isRunning = false;
}

void Game::run() {
  isRunning = true;
  threads[0] = std::thread(&Game::runOutput, this);
  threads[1] = std::thread(&Game::runActions, this);
  while(isRunning){}
}

void Game::cleanup() {
  for (auto &thread : this->threads) {
    thread.join();
  }
}
