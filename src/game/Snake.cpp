#include "Snake.hpp"
#include <ncurses.h>
#include "../debug/print.hpp"
#include "Game.hpp"

bool Snake::snake_move(char chinput, char lastinput, int*y, int*x, WINDOW* win) {
    switch (chinput) {
        case 'w': 
            if(lastinput != 's') {
                (*y)--; 
                return true;
            }
            return false;
        case 's': 
            if(lastinput != 'w') {
                (*y)++; 
                return true;
            }
            return false;
        case 'a': 
            if(lastinput != 'd') {
                (*x)--; 
                return true;
            }
            return false;
        case 'd': 
            if(lastinput != 'a') {
                (*x)++; 
                return true;
            }
            return false;
        case 'p':
            Game::PauseGame(win);
            return false;
        default: return false;
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
    this->cibo = new Object{nullptr, 0, 0, 'a'};
    generateFood();
}

void Snake::generateFood() {
    this->cibo->y = (int)(rand() % (height - 2)) + 1;
    this->cibo->x = (int)(rand() % (width  - 2)) + 1;
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