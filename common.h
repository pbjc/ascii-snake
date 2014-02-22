#ifndef ASCII_SNAKE_COMMON_H_
#define ASCII_SNAKE_COMMON_H_

struct Location {
  Location(int xVal, int yVal) : x(xVal), y(yVal) { }
  int x;
  int y; 
};

enum class direction { UP, DOWN, LEFT, RIGHT };
enum class boardValue { EMPTY, SNAKE, FOOD };

#endif
