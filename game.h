#ifndef ASCII_SNAKE_GAME_H_
#define ASCII_SNAKE_GAME_H_

#include "snake.h"

class Game {
  public:
    Game(int boardWidth, int boardHeight);
    ~Game();
    void newGame(int startX, int startY);
    void newGame(int startX, int startY, direction dir, int len);
    bool isActive();
    void setDir(direction dir);
    const int** getBoard();
    friend std::ostream& operator<<(std::ostream& os, const Game& game);
  private:
    int width_;
    int height_;
    int** board;
    Snake snake_;
    bool gameRunning;
    Game(const Game& game);
    Game& operator=(const Game& game) { return *this; }
};

#endif
