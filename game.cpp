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

void Game::newGame(int startX, int startY) {
  clearBoard();
  snake_ = new Snake(startX, startY);
  drawBoard();
  gameRunning_ = true;
}

void Game::newGame(int startX, int startY, direction dir, int len) {
  clearBoard();
  snake_ = new Snake(startX, startY, dir, len);
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

boardValue Game::getValueAt(int x, int y) const {
  return board_[y * width_ + x];
}

std::ostream& operator<<(std::ostream& os, const Game& game) {
  using std::cout;
  for (int c = 0; c < game.width_; c++) {
    cout << "[";
    for (int r = 0; r < game.height_; r++) {
      cout << int(game.getValueAt(r, c));
      if (r < game.height_ - 1) {
        cout << ", ";
      }
    }
    cout << "]" << std::endl;
  }
  return os;
}

boardValue& Game::accessBoard(int x, int y) {
  if (x < 0 || x > width_ || y < 0 || y > height_) {
    std::cerr << "Error: Location out of bounds. [" << x << ", " << y << "] ";
    std::cerr << "is not within the " << width_ << "x" << height_ << " board.";
    std::cerr << std::endl;
    exit(-1);
  }
  return board_[y * width_ + x];
}

void Game::clearBoard() {
  for (int x = 0; x < width_; x++) {
    for (int y = 0; y < width_; y++) {
      accessBoard(x, y) = boardValue::EMPTY;
    }
  }
}

void Game::drawBoard() {
  snake_->resetIterator();
  while (snake_->hasNextLoc()) {
    Snake::Location loc = snake_->nextLoc();
    accessBoard(loc.x, loc.y) = boardValue::SNAKE;
  }
}
