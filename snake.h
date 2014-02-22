#ifndef ASCII_SNAKE_SNAKE_H_
#define ASCII_SNAKE_SNAKE_H_

#include <iostream>
#include "common.h"

class Snake {
  public:
    Snake();
    Snake(int startX, int startY);
    Snake(int startX, int startY, direction dir, int len);
    Snake(const Snake&) = delete;
    Snake& operator=(const Snake&) = delete;
    ~Snake();

    void setDir(direction dir);
    void move();
    void feed();

    struct Location {int x; int y;};
    void resetIterator();
    bool hasNextLoc();
    Location nextLoc();

    friend std::ostream& operator<<(std::ostream& os, const Snake& snake);
  private:
    struct Node {
      int x;
      int y;
      Node* next;
    };

    Node* head_;
    int length_;
    direction dir_;
    Node* iter_;

    void move(Node* node);
};

#endif
