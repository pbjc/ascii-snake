#ifndef ASCII_SNAKE_COMMON_H_
#define ASCII_SNAKE_COMMON_H_

#include <iostream>

struct Location {
  int x;
  int y; 
  Location() { x = 0; y = 0; }
  Location(int xVal, int yVal) : x(xVal), y(yVal) { }
  friend std::ostream& operator<<(std::ostream& os, const Location loc) {
    os << "[" << loc.x << ", " << loc.y << "]";
    return os;
  }
};

enum class direction { UP, DOWN, LEFT, RIGHT };
enum class boardValue { EMPTY, SNAKE, FOOD };

#endif
