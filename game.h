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

    bool isActive() const;
    void setDirection(direction dir);
    void update();
    board_value getValueAt(Location loc) const;

    friend std::ostream& operator<<(std::ostream& os, const Game& game);
  private:
    board_value& accessBoard(Location loc);
    void clearBoard();
    void drawBoard();

    int width_;
    int height_;
    board_value* board_;
    Snake* snake_;
    bool gameRunning_;

    Game(const Game&);
    Game& operator=(const Game&);
};

#endif
