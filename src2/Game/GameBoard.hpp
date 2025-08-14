#ifndef GAME_BOARD_HPP
#define GAME_BOARD_HPP

#include <cstring>
#include <ncurses.h>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <ctime>

#define MAX_TIME 300

static int max_x,max_y,score, height, width;
static int TIMEOUT = 50;
WINDOW* drawBoard();

int getMillis() ;
char getInput(WINDOW*win);

void startGame();


#endif