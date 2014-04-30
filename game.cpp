#include "game.h"
#include <cstdlib>
#include <iostream>
#include "common.h"
#include "snake.h"

Game::Game(int boardWidth, int boardHeight) {
  if (boardWidth < 3 || boardHeight < 3) {
    std::cerr << "Error: Board dimensions must be at least 3x3." << std::endl;
    exit(EXIT_FAILURE);
  }
  width_ = boardWidth;
  height_ = boardHeight;
  board_  = new board_value[width_ * height_];
}

Game::~Game() {
  delete [] board_;
  delete snake_;
}

void Game::newGame(Location startLocation) {
  clearBoard();
  delete snake_;
  snake_ = new Snake(startLocation);
  drawSnake();
  placeNewFood();
  gameRunning_ = true;
}

void Game::newGame(Location startLocation, direction dir, int len) {
  clearBoard();
  delete snake_;
  snake_ = new Snake(startLocation, dir, len);
  drawSnake();
  placeNewFood();
  gameRunning_ = true;
}

bool Game::isActive() const {
  return gameRunning_;
}

void Game::setDirection(direction dir) {
  snake_->setDirection(dir);
}

void Game::update() {
  if (!gameRunning_) {
    return;
  }
  Location newLoc = snake_->getHeadLocation().getAdjacentLocation(
                    snake_->getDirection());
  if (isOutOfBounds(newLoc) || getValueAt(newLoc) == board_value::SNAKE) {
    gameRunning_ = false;
    return;
  } else if (getValueAt(newLoc) == board_value::FOOD) {
    undrawSnake();
    snake_->feed();
    drawSnake();
    placeNewFood();
  } else {
    undrawSnake();
    snake_->move();
    drawSnake();
  }
}

board_value Game::getValueAt(Location loc) const {
  if (isOutOfBounds(loc)) {
    std::cerr << "Error: Location out of bounds. " << loc;
    std::cerr << "is not within the " << width_ << "x" << height_ 
              << " board dimensions.";
    std::cerr << std::endl;
    exit(EXIT_FAILURE);
  }
  return board_[loc.y * width_ + loc.x];
}

int Game::getSnakeLength() const {
  return snake_->getLength();
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

bool Game::isOutOfBounds(Location loc) const {
  return loc.x < 0 || loc.x >= width_ || loc.y < 0 || loc.y >= height_;
}

board_value& Game::accessBoard(Location loc) {
  if (isOutOfBounds(loc)) {
    std::cerr << "Error: Location out of bounds. " << loc;
    std::cerr << "is not within the " << width_ << "x" << height_ 
              << " board dimensions.";
    std::cerr << std::endl;
    exit(EXIT_FAILURE);
  }
  return board_[loc.y * width_ + loc.x];
}

void Game::clearBoard() {
  for (int x = 0; x < width_; x++) {
    for (int y = 0; y < height_; y++) {
      accessBoard({x, y}) = board_value::EMPTY;
    }
  }
}

void Game::drawSnake() {
  snake_->resetIterator();
  while (snake_->hasNextLocation()) {
    accessBoard(snake_->nextLocation()) = board_value::SNAKE;
  }
}

void Game::undrawSnake() {
  snake_->resetIterator();
  while (snake_->hasNextLocation()) {
    accessBoard(snake_->nextLocation()) = board_value::EMPTY;
  }
}

void Game::placeNewFood() {
  if (width_ * height_ == snake_->getLength()) {
    gameRunning_ = false;
  }
  int randIndex = rand() % (width_ * height_ - snake_->getLength());
  for (int x = 0; x < width_; x++) {
    for (int y = 0; y < height_; y++) {
      if (getValueAt({x, y}) == board_value::EMPTY) {
        if (randIndex == 0) {
          accessBoard({x, y}) = board_value::FOOD;
          return;
        } else {
          randIndex--;
        }
      }
    }
  }
}
