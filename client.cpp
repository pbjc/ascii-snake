#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <curses.h>
#include "common.h"
#include "game.h"

static Game* game;
static int width;
static int height;
static constexpr int STARTLENGTH = 3;

static void init();
static void setGameInput();
static void drawGame();
static void showGameOver();
static void wait(float seconds);

int main() {
  init();

  getmaxyx(stdscr, height, width);
  height -= 2;
  width -= 2;
  game = new Game(width, height);
  game->newGame({width / 3, height / 3}, direction::RIGHT, STARTLENGTH);

  wborder(stdscr, '|', '|', '-', '-', '+', '+', '+', '+');
  drawGame();
  refresh();

  while (true) {
    setGameInput();
    game->update();
    if (!game->isActive()) {
      showGameOver();
      nodelay(stdscr, FALSE);
      if (getch() == 'q') {
        break;
      } else {
        game->newGame({width / 3, height / 3}, direction::RIGHT, STARTLENGTH);
        nodelay(stdscr, TRUE);
      }
    }
    drawGame();
    refresh();
    wait(0.1f);
  }

  endwin();
  return 0;
}

static void init() {
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  noecho();
  curs_set(0);
  srand(time(NULL));
}

static void setGameInput() {
  int ch = getch();
  if (ch == KEY_UP) {
    game->setDirection(direction::UP);
  } else if (ch == KEY_RIGHT) {
    game->setDirection(direction::RIGHT);
  } else if (ch == KEY_DOWN) {
    game->setDirection(direction::DOWN);
  } else if (ch == KEY_LEFT) {
    game->setDirection(direction::LEFT);
  }
}

static void drawGame() {
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      if (game->getValueAt({x, y}) == board_value::SNAKE) {
        mvaddch(y + 1, x + 1, ' ' | A_STANDOUT);
      } else if (game->getValueAt({x, y}) == board_value::FOOD) {
        mvaddch(y + 1, x + 1, '*');
      } else {
        mvaddch(y + 1, x + 1, ' ');
      }
    }
  }
}

static void showGameOver() {
  const char* gameOver;
  if (game->getSnakeLength() == width * height) {
    gameOver = "You died. Press q to quit, or any other key to play again.";
  } else {
    gameOver = "You won! Press q to quit, or any other key to play again.";
  }
  mvprintw(height / 2, width / 2 - strlen(gameOver) / 2, gameOver);
  refresh();
}

static void wait(float seconds) {
  clock_t start = clock();
  clock_t delay = seconds * CLOCKS_PER_SEC;
  while(clock() - start < delay);
}
