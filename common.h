#ifndef ASCII_SNAKE_COMMON_H_
#define ASCII_SNAKE_COMMON_H_

#include <iostream>

enum class direction { UP, RIGHT, DOWN, LEFT };
enum class board_value { EMPTY, SNAKE, FOOD };

struct Location {
  Location() { x = 0; y = 0; }
  Location(int xVal, int yVal) : x(xVal), y(yVal) { }
  Location getAdjacentLocation(direction dir) const {
    int newX = x + (dir == direction::LEFT ? -1 :
                        dir == direction::RIGHT ? 1 : 0);
    int newY = y + (dir == direction::UP ? -1 :
                        dir == direction::DOWN ? 1 : 0);
    return {newX, newY};
  }
  friend std::ostream& operator<<(std::ostream& os, const Location loc) {
    os << "[" << loc.x << ", " << loc.y << "]";
    return os;
  }
  int x;
  int y;
};

#endif
