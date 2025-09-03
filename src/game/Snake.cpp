#include "Snake.hpp"
#include <ncurses.h>
#include "../debug/print.hpp"

bool Snake::snake_move(char chinput, int*y, int*x) {
    switch (chinput) {
        case 'w': (*y)--; break;
        case 's': (*y)++; break;
        case 'a': (*x)--; break;
        case 'd': (*x)++; break;
        default:    return false;
    }
    return true;
}

void Snake::initSnake(){
    this->head = new Object{nullptr, y, x, 'O'};
    this->tail = head;
    for(int i = 0; i < snakeSize; i++) {
        Object*body = new Object{tail, y, x-i, 'o'};
        tail = body;
        dbg::print_debug_hell_yeah("snake init #", i, " tail.x = ", tail->x);
    }
    this->cibo = new Object{nullptr, (int)(rand()%(height-2)), (int)(rand()%(width-2)), 'a'};
}
void Snake::setParam(int width, int height){
    this->height = height; 
    this->width = width; 
}

Snake::Snake(int snakeSize,int x, int y){
    this->snakeSize = snakeSize;
    this->x = x;
    this->y = y;
}