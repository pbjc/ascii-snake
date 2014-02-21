#include <iostream>
#include "snake.h"

int main() {
  Snake snake(10, 10, direction::LEFT, 5);
  std::cout << "created snake of length 5 at location 10, 10 facing left" << std::endl;
  std::cout << snake;
  snake.move();
  std::cout << "moved snake" << std::endl;
  std:: cout << snake;
  snake.setDir(direction::UP);
  snake.move();
  std::cout << "moved snake up" << std::endl;
  std::cout << snake;
  snake.feed();
  std::cout << "fed snake" << std::endl;
  std::cout << snake;
  std::cout << "iterating through snake" << std::endl;
  snake.resetIterator();
  while (snake.hasNextLoc()) {
    Snake::Location loc = snake.nextLoc();
    std::cout << "[" << loc.x << ", " << loc.y << "]";
    if (snake.hasNextLoc()) {
      std::cout << ", ";
    }
  }
  std::cout << std::endl;
  return 0;
}
