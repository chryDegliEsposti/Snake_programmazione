#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <ncurses.h>

struct object {
    object*next;
    int y;
    int x;
    char type;
};

object *head,*tail;
int y, x, snakelen, speed;

void drawSnake(WINDOW* board);
bool snake_move(char chinput, int*y, int*x);

#endif