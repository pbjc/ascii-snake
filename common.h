#ifndef ASCII_SNAKE_COMMON_H_
#define ASCII_SNAKE_COMMON_H_

#include <iostream>

enum class direction { UP, RIGHT, DOWN, LEFT };
enum class board_value { EMPTY, SNAKE, FOOD };

struct Location {
  Location() { x = 0; y = 0; }
  Location(int xVal, int yVal) : x(xVal), y(yVal) { }
  Location getAdjacentLocation(direction dir) const {
    if (dir == direction::UP) return {x, y - 1};
    else if (dir == direction::RIGHT) return {x + 1, y};
    else if (dir == direction::DOWN) return {x, y + 1};
    else if (dir == direction::LEFT) return {x + 1, y};
  }
  friend std::ostream& operator<<(std::ostream& os, const Location loc) {
    os << "[" << loc.x << ", " << loc.y << "]";
    return os;
  }
  int x;
  int y;
};

#endif
