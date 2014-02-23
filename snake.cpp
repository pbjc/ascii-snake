#include "snake.h"
#include <cstdlib>
#include <iostream>
#include "common.h"

Snake::Snake() {
  head_ = new Node{{0, 0}, nullptr};
  length_ = 1;
  direction_ = direction::RIGHT;
  lastTailLoc = {0, 0};
}

Snake::Snake(Location startLocation) {
  head_ = new Node{startLocation, nullptr};
  length_ = 1;
  direction_ = direction::LEFT;
  lastTailLoc = {startLocation.x, startLocation.y};
}

Snake::Snake(Location startLocation, direction dir, int length) {
  if (length < 1) {
    std::cerr << "Error: Snake length must be greater than zero." << std::endl;
    exit(EXIT_FAILURE);
  }
  head_ = new Node{startLocation, nullptr};
  Node* curr = head_;
  int buildDirX = dir == direction::LEFT ? 1 :
                  dir == direction::RIGHT ? -1 : 0;
  int buildDirY = dir == direction::DOWN ? -1 :
                  dir == direction::UP ? 1 : 0;
  for (int i = 1; i < length; i++) {
    int nextX = startLocation.x + i * buildDirX;
    int nextY = startLocation.y + i * buildDirY;
    curr->next = new Node{{nextX, nextY}, nullptr};
    curr = curr->next;
    if (i == length - 1) {
      lastTailLoc = {curr->x + buildDirX, curr->y + buildDirY};
    }
  }
  length_ = length;
  direction_ = dir;
}

Snake::~Snake() {
  Node* temp;
  while (head_ != nullptr) {
    temp = head_;
    head_ = head_->next;
    delete temp;
  }
}

void Snake::setDirection(direction dir) {
  direction_ = dir;
}

void Snake::move() {
  move(head_);
  head_->x += direction_ == direction::LEFT ? -1 :
              direction_ == direction::RIGHT ? 1 : 0;
  head_->y += direction_ == direction::DOWN ? 1 :
              direction_ == direction::UP ? -1 : 0;
}

void Snake::move(Node* node) {
  if (node->next == nullptr) {
    lastTailLoc = {node->x, node->y};
    return;
  }
  move(node->next);
  node->next->x = node->x;
  node->next->y = node->y;
}

void Snake::feed() {
  Node* curr = head_;
  while (curr->next != nullptr) {
    curr = curr->next;
  }
  curr->next = new Node{lastTailLoc, nullptr};
}

int Snake::getLength() const {
  return length_;
}

void Snake::resetIterator() {
  iter_ = head_;
}

bool Snake::hasNextLoc() {
  return iter_ != nullptr;
}

Location Snake::nextLoc() {
  Location loc = {iter_->x, iter_->y};
  iter_ = iter_->next;
  return loc;
}

std::ostream& operator<<(std::ostream& os, const Snake& snake) {
  os << int(snake.direction_) << ":";
  Snake::Node* curr = snake.head_;
  while (curr != nullptr) {
    os << *curr;
    if (curr->next != nullptr) {
      os << ", ";
    }
    curr = curr->next;
  }
  os << std::endl;
  return os;
}
