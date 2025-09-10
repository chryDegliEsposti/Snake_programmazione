#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <stdlib.h>
#include <ncurses.h>

struct Object {
    Object*next;
    int y;
    int x;
    char type;
};

class Snake{
    public:

    Snake(int snakeSize,int x, int y);
    int snakeSize;
    int x , y;
    int width ;
    int height;
    Object *head;
    Object *tail;
    Object *cibo;

    bool snake_move(char chinput, char lastinput, int*y, int*x, WINDOW* win) ;
    void initSnake();
    void setParam(int width, int height);
    void generateFood();

    
};

#endif