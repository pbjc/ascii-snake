#ifndef ASCII_SNAKE_SNAKE_H_
#define ASCII_SNAKE_SNAKE_H_

#include <iostream>
#include "common.h"

class Snake {
  public:
    Snake();
    Snake(Location startLocation);
    Snake(Location startLocation, direction dir, int length);
    ~Snake();

    void setDirection(direction dir);
    void move();
    void feed();

    void resetIterator();
    bool hasNextLoc();
    Location nextLoc();

    friend std::ostream& operator<<(std::ostream& os, const Snake& snake);
  private:
    struct Node : public Location {
      Node* next;
      Node(Location loc, Node* nextNode) : Location(loc.x, loc.y), next(nextNode) { }
    };

    void move(Node* node);

    Node* head_;
    Node* iter_;
    Location lastTailLoc;
    int length_;
    direction direction_;

    Snake(const Snake&);
    Snake& operator=(const Snake&);
};

#endif
