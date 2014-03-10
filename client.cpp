#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <curses.h>
#include "common.h"
#include "game.h"

static Game* game;
static int screenWidth;
static int screenHeight;
static int gameWidth;
static int gameHeight;
static constexpr int STARTLENGTH = 3;

static void init();
static void setGameInput();
static void drawBorder();
static void drawGame();
static void showGameOver();
static void wait(float seconds);

int main() {
  init();

  while (true) {
    setGameInput();
    game->update();
    if (!game->isActive()) {
      showGameOver();
      wait(.1f);
      getch();
      nodelay(stdscr, FALSE);
      int ch = getch();
      if (ch == 'q' || ch == 'Q') {
        break;
      } else {
        game->newGame({gameWidth / 3, gameHeight / 3}, direction::RIGHT, STARTLENGTH);
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

  getmaxyx(stdscr, screenHeight, screenWidth);
  gameHeight = screenHeight - 2;
  gameWidth = (screenWidth - 2 - (screenWidth % 2 == 0 ? 0 : 1)) / 2;
  game = new Game(gameWidth, gameHeight);
  game->newGame({gameWidth / 3, gameHeight / 3}, direction::RIGHT, STARTLENGTH);

  drawBorder();
  drawGame();
  refresh();
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

static void drawBorder() {
  int xOffset = screenWidth % 2 == 0 ? 0 : 1;
  mvaddch(0, 0, '+');
  mvaddch(0, screenWidth - 1 - xOffset, '+');
  mvaddch(screenHeight - 1, 0, '+');
  mvaddch(screenHeight - 1, screenWidth - 1 - xOffset, '+');
  for (int x = 1; x < screenWidth - 1 - xOffset; x++) {
    mvaddch(0, x, '-');
    mvaddch(screenHeight - 1, x, '-');
  }
  for (int y = 1; y < screenHeight - 1; y++) {
    mvaddch(y, 0, '|');
    mvaddch(y, screenWidth - 1 - xOffset, '|');
  }
}

static void drawGame() {
  for (int x = 0; x < gameWidth; x++) {
    for (int y = 0; y < gameHeight; y++) {
      Location loc = {x, y};
      if (game->getValueAt(loc) == board_value::SNAKE) {
        attron(A_STANDOUT);
        mvprintw(y + 1, x * 2 + 1, "  ");
        attroff(A_STANDOUT);
      } else if (game->getValueAt(loc) == board_value::FOOD) {
        mvprintw(y + 1, x * 2 + 1, "><");
      } else {
        mvprintw(y + 1, x * 2 + 1, "  ");
      }
    }
  }
}

static void showGameOver() {
  const char* gameOver;
  if (game->getSnakeLength() == gameWidth * gameHeight) {
    gameOver = "You won! Press q to quit, or any other key to play again.";
  } else {
    gameOver = "You died. Press q to quit, or any other key to play again.";
  }
  mvprintw(screenHeight / 2, screenWidth / 2 - strlen(gameOver) / 2, gameOver);
  refresh();
}

static void wait(float seconds) {
  clock_t start = clock();
  clock_t delay = seconds * CLOCKS_PER_SEC;
  while(clock() - start < delay);
}
