#ifndef ASCII_SNAKE_GAME_H_
#define ASCII_SNAKE_GAME_H_

#include <iostream>
#include "common.h"

class Snake;

class Game {
  public:
    Game(int boardWidth, int boardHeight);
    ~Game();

    void newGame(int startX, int startY);
    void newGame(int startX, int startY, direction dir, int len);

    bool isActive();
    void setDir(direction dir);
    void update();
    const char* getBoard();

    friend std::ostream& operator<<(std::ostream& os, const Game& game);
  private:
    int width_;
    int height_;
    char* board_;
    Snake* snake_;
    bool gameRunning_;

    char accessBoard(int x, int y) const;
    char& accessBoard(int x, int y);
    void clearBoard();
    void drawBoard();
};

#endif
