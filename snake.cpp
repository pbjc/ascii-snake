#include "snake.h"
#include <cstdlib>
#include <iostream>
#include "common.h"

Snake::Snake() {
  head_ = new Node{{0, 0}, nullptr};
  length_ = 1;
  dir_ = direction::RIGHT;
}

Snake::Snake(Location startLoc) {
  head_ = new Node{startLoc, nullptr};
  length_ = 1;
  dir_ = direction::LEFT;
}

Snake::Snake(Location startLoc, direction dir, int len) {
  if (len < 1) {
    std::cerr << "Error: Snake length must be greater than zero." << std::endl;
    exit(EXIT_FAILURE);
  }
  head_ = new Node{startLoc, nullptr};
  Node* curr = head_;
  int buildDirX = dir == direction::LEFT ? 1 :
                  dir == direction::RIGHT ? -1 : 0;
  int buildDirY = dir == direction::DOWN ? -1 :
                  dir == direction::UP ? 1 : 0;
  for (int i = 1; i < len; i++) {
    int nextX = startLoc.x + i * buildDirX;
    int nextY = startLoc.y + i * buildDirY;
    curr->next = new Node{{nextX, nextY}, nullptr};
    curr = curr->next;
  }
  length_ = len;
  dir_ = dir;
}

Snake::~Snake() {
  Node* temp;
  while (head_ != nullptr) {
    temp = head_;
    head_ = head_->next;
    delete temp;
  }
}

void Snake::setDir(direction dir) {
  dir_ = dir;
}

void Snake::move() {
  move(head_);
  head_->x += dir_ == direction::LEFT ? -1 :
              dir_ == direction::RIGHT ? 1 : 0;
  head_->y += dir_ == direction::DOWN ? 1 :
              dir_ == direction::UP ? -1 : 0;
}

void Snake::move(Node* node) {
  if (node->next == nullptr) {
    return;
  }
  move(node->next);
  node->next->x = node->x;
  node->next->y = node->y;
}

void Snake::feed() {
  int newX = head_->x + (dir_ == direction::LEFT ? -1 :
                         dir_ == direction::RIGHT ? 1 : 0);
  int newY = head_->y + (dir_ == direction::DOWN ? 1:
                         dir_ == direction::UP ? -1 : 0);
  head_ = new Node{{newX, newY}, head_};
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
  os << int(snake.dir_) << ":";
  Snake::Node* curr = snake.head_;
  while (curr != nullptr) {
    os << "[" << curr->x << ", " << curr->y << "]";
    if (curr->next != nullptr) {
      os << ", ";
    }
    curr = curr->next;
  }
  os << std::endl;
  return os;
}
