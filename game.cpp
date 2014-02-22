#include "game.h"
#include <cstdlib>
#include <iostream>
#include "common.h"
#include "snake.h"

Game::Game(int boardWidth, int boardHeight) {
  width_ = boardWidth;
  height_ = boardHeight;
  board_  = new boardValue[width_ * height_];
}

Game::~Game() {
  delete [] board_;
}

void Game::newGame(Location startLoc) {
  clearBoard();
  snake_ = new Snake(startLoc);
  drawBoard();
  gameRunning_ = true;
}

void Game::newGame(Location startLoc, direction dir, int len) {
  clearBoard();
  snake_ = new Snake(startLoc, dir, len);
  drawBoard();
  gameRunning_ = true;
}

bool Game::isActive() {
  return gameRunning_;
}

void Game::setDir(direction dir) {
  snake_->setDir(dir);
}

void Game::update() {
  snake_->move();
  // do stuff
  clearBoard();
  drawBoard();
}

boardValue Game::getValueAt(Location loc) const {
  return board_[loc.y * width_ + loc.x];
}

std::ostream& operator<<(std::ostream& os, const Game& game) {
  using std::cout;
  for (int c = 0; c < game.width_; c++) {
    cout << "[";
    for (int r = 0; r < game.height_; r++) {
      cout << int(game.getValueAt({r, c}));
      if (r < game.height_ - 1) {
        cout << ", ";
      }
    }
    cout << "]" << std::endl;
  }
  return os;
}

boardValue& Game::accessBoard(Location loc) {
  if (loc.x < 0 || loc.x > width_ || loc.y < 0 || loc.y > height_) {
    std::cerr << "Error: Location out of bounds. [" << loc.x << ", " << loc.y << "] ";
    std::cerr << "is not within the " << width_ << "x" << height_ << " board.";
    std::cerr << std::endl;
    exit(-1);
  }
  return board_[loc.y * width_ + loc.x];
}

void Game::clearBoard() {
  for (int x = 0; x < width_; x++) {
    for (int y = 0; y < width_; y++) {
      accessBoard({x, y}) = boardValue::EMPTY;
    }
  }
}

void Game::drawBoard() {
  snake_->resetIterator();
  while (snake_->hasNextLoc()) {
    accessBoard(snake_->nextLoc()) = boardValue::SNAKE;
  }
}
