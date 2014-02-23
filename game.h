#ifndef ASCII_SNAKE_GAME_H_
#define ASCII_SNAKE_GAME_H_

#include <iostream>
#include "common.h"

class Snake;

class Game {
  public:
    Game(int boardWidth, int boardHeight);
    ~Game();

    void newGame(Location startLocation);
    void newGame(Location startLocation, direction dir, int len);

    void setDirection(direction dir);
    void update();

    bool isActive() const;
    board_value getValueAt(Location loc) const;
    int getSnakeLength() const;

    friend std::ostream& operator<<(std::ostream& os, const Game& game);
  private:
    board_value& accessBoard(Location loc);
    bool isOutOfBounds(Location loc) const;
    void clearBoard();
    void updateAndDrawSnake();
    void undrawSnake();
    void placeNewFood();

    int width_;
    int height_;
    board_value* board_;
    Snake* snake_;
    bool gameRunning_;

    Game(const Game&);
    Game& operator=(const Game&);
};

#endif
