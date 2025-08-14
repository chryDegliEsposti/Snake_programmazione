#ifndef GRAPHIC_FUNCS_HPP

#define GRAPHIC_FUNCS_HPP

#include <cstring>
#include <ncurses.h>
#include <ncurses.h>

struct WindowRegionNode {
    int posY, posX;
};

void init();
void endGame();
WINDOW *new_bordered_window(int height, int width, int y, int x);

void drawFilledCircle(int center_y, int center_x, int radius_x, int radius_y,int color) ;

#endif