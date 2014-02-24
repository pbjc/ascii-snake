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
    int getLength() const;
    Location getNewHeadLocation() const;

    void resetIterator();
    bool hasNextLocation();
    Location nextLocation();

    friend std::ostream& operator<<(std::ostream& os, const Snake& snake);
  private:
    Node* head_;
    Node* tail_;
    Node* iter_;
    int length_;
    direction direction_;

    struct Node : public Location {
      Node(Location loc, Node* nextNode) : Location(loc.x, loc.y), next(nextNode) { }
      Node* next;
    };

    Snake(const Snake&);
    Snake& operator=(const Snake&);
};

#endif
