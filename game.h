#ifndef ASCII_SNAKE_GAME_H_
#define ASCII_SNAKE_GAME_H_

#include <iostream>
#include "common.h"

class Snake;

class Game {
  public:
    Game(int boardWidth, int boardHeight);
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    ~Game();

    void newGame(Location startLoc);
    void newGame(Location startLoc, direction dir, int len);

    bool isActive() const;
    void setDir(direction dir);
    void update();
    board_value getValueAt(Location loc) const;

    friend std::ostream& operator<<(std::ostream& os, const Game& game);
  private:
    int width_;
    int height_;
    board_value* board_;
    Snake* snake_;
    bool gameRunning_;

    board_value& accessBoard(Location loc);
    void clearBoard();
    void drawBoard();
};

#endif
