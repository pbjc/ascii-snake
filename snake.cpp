#include "snake.h"
#include <iostream>

Snake::Snake(int startX, int startY) {
  head_ = new Node{startX, startY, nullptr};
  length_ = 1;
  dir_ = direction::LEFT;
}

Snake::Snake(int startX, int startY, direction dir, int len) {
  head_ = new Node{startX, startY, nullptr};
  Node* curr = head_;
  int buildDirX = dir == direction::LEFT ? 1 :
                  dir == direction::RIGHT ? -1 : 0;
  int buildDirY = dir == direction::DOWN ? -1 :
                  dir == direction::UP ? 1 : 0;
  for (int i = 1; i < len; i++) {
    int nextX = startX + i * buildDirX;
    int nextY = startY + i * buildDirY;
    curr->next = new Node{nextX, nextY, nullptr};
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
  head_ = new Node{newX, newY, head_};
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
