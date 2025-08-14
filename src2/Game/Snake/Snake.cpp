#include "Snake.hpp"

void drawSnake(WINDOW *board){
    head = new object{nullptr, y, x, 'O'};
    tail = head;
    for(int i = 1; i < snakelen; i++) {
        object* body = new object{tail, y, x - i, 'o'};
        tail = body;
    }
    object* cur = head;
    while(cur) {
        mvwaddch(board, cur->y, cur->x, cur->type);
        cur = cur->next;
    }
}


bool snake_move(char chinput, int*y, int*x) {
    switch (chinput) {
        case 'w': (*y)--; break;
        case 's': (*y)++; break;
        case 'a': (*x)--; break;
        case 'd': (*x)++; break;
        default:    return false;
    }
    return true;
}