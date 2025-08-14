#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <stdlib.h>
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

    bool snake_move(char chinput, int*y, int*x) ;
    void initSnake();
    void setParam();

    
};

#endif