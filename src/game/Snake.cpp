#include "Snake.hpp"
#include <ncurses.h>

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
    }
    this->cibo = new Object{nullptr, (int)(rand()%(height-2)), (int)(rand()%(width-2)), 'a'};
}
void Snake::setParam(){
    int maxX = getmaxx(stdscr);
    int maxY = getmaxy(stdscr);
    this->height = maxY*0.8; 
    this->width = maxX*0.8; 
}

Snake::Snake(int snakeSize,int x, int y){
    this->snakeSize = snakeSize;
    this->x = x;
    this->y = y;
    setParam();
    initSnake();
}