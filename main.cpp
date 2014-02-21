#include <iostream>
#include "common.h"
#include "game.h"

int main() {
  Game game = Game(15, 15);
  game.newGame(5, 5, direction::LEFT, 5);
  std::cout << game << std::endl;
  game.update();
  std::cout << game << std::endl;
  game.setDir(direction::UP);
  game.update();
  std::cout << game << std::endl;
}
