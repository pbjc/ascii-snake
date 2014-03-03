#include "snake.h"
#include <cstdlib>
#include <iostream>
#include "common.h"

Snake::Snake() {
  head_ = new Node{{0, 0}, nullptr};
  tail_ = head_;
  length_ = 1;
  direction_ = direction::RIGHT;
}

Snake::Snake(Location startLocation) {
  head_ = new Node{startLocation, nullptr};
  tail_ = head_;
  length_ = 1;
  direction_ = direction::LEFT;
}

Snake::Snake(Location startLocation, direction dir, int length) {
  if (length < 1) {
    std::cerr << "Error: Snake length must be greater than zero." << std::endl;
    exit(EXIT_FAILURE);
  }
  head_ = new Node{startLocation, nullptr};
  Node* curr = head_;
  if (length == 1) {
    tail_ = head_;
  }
  direction buildDir = direction((int(dir) + 2) % 4);
  Location nextLoc = startLocation;
  for (int i = 1; i < length; i++) {
    nextLoc = nextLoc.getAdjacentLocation(buildDir);
    curr->next = new Node{nextLoc, nullptr};
    curr = curr->next;
    if (i == length - 1) {
      tail_ = curr;
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
  Node* newTail = head_;
  if (length_ > 1) {
    while (newTail->next->next != nullptr) {
      newTail = newTail->next;
    }
  }
  Location newLoc = head_->getAdjacentLocation(direction_);
  tail_->x = newLoc.x;
  tail_->y = newLoc.y;
  tail_->next = head_;
  head_ = tail_;
  tail_ = newTail;
  newTail->next = nullptr;
}

void Snake::feed() {
  head_ = new Node{head_->getAdjacentLocation(direction_), head_};
  length_++;
}

Location Snake::getHeadLocation() const {
  return *head_;
}

direction Snake::getDirection() const {
  return direction_;
}

int Snake::getLength() const {
  return length_;
}

void Snake::resetIterator() {
  iter_ = head_;
}

bool Snake::hasNextLocation() {
  return iter_ != nullptr;
}

Location Snake::nextLocation() {
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
