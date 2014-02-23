#include <iostream>
#include "common.h"
#include "game.h"

int main() {
  Game game(10, 10);
  game.newGame({5, 5}, direction::LEFT, 3);
  std::cout << game << std::endl;
  game.update();
  std::cout << game << std::endl;
  game.setDirection(direction::UP);
  game.update();
  std::cout << game;
}
