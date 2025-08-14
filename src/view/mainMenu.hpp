#ifndef MAIN_MENU_HPP

#define MAIN_MENU_HPP
#include "graphicFuncs.hpp"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ncurses.h>
#include <cstring>
#include <cmath>
#include "graphicFuncs.hpp"

#define COLOR_DARK_GREEN 5

class mainMenu {
    public:

    // snake pattern testa: 8 righe x 14 cols
    static const int SNAKE_HEAD_H = 8;
    static const int SNAKE_HEAD_W = 14;
    static constexpr int SNAKE_HEAD[SNAKE_HEAD_H][SNAKE_HEAD_W] = {

    {          0,0,5,5,5,5,5,5,5,0, 0, 0, 0, 0 },  
    {          0,5,5,1,1,1,1,1,1,5, 5, 0, 0, 0 },  
    {          5,5,1,1,1,3,1,1,1,1, 5, 5, 0, 0 },   
    {          5,1,1,1,1,1,1,1,1,1, 1, 5, 5, 0 },   
    {          4,4,1,1,1,1,1,1,1,1, 1, 5, 5, 0 },  
    {          5,5,1,1,1,1,1,1,1,1, 5, 5, 0, 0 },  
    {          0,5,5,1,1,1,1,1,1,5, 5, 0, 0, 0 },  
    {          0,0,5,5,5,5,5,5,5,0, 0, 0, 0, 0 }   
    };

    // Snake pattern del corpo: 8 righe x 10 cols
    // "1" (verde) per bordi e "2" (binaco) per l'interno
    static const int SNAKE_BODY_H = 4;
    static const int SNAKE_BODY_W = 15;
    static constexpr int SNAKE_BODY[SNAKE_BODY_H][SNAKE_BODY_W] = 
    {
    {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5}
    };
    
    static void init_colorPairs();

    static void drawShape(int originY, int originX, int height, int width, const int shape[][SNAKE_HEAD_W]);

    static void drawShape2(int originY, int originX, int height, int width, const int shape[][SNAKE_BODY_W]);

    static void drawSnake(int originY, int originX, int numBodySegments);

    void updateWindowColor(const int numChoise, int color);

    static void repaintAll(int max_x, int max_y, int selected);

    static void drawVerticalSnake(int startY);

    static int page(int max_x, int max_y);

    void insertNode(WindowRegionNode data);

    static void initPage(int max_x,int max_y);

    static int mainPage();
};


#endif