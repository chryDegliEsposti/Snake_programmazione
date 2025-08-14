#include "mainMenu.hpp"
#include "graphicFuncs.hpp"
#include <ncurses.h>
#include <cmath>


static WindowRegionNode windArr[100];

const static int RADIUS_CIRCLE_X = 15;
const static int RADIUS_CIRCLE_Y = 3;


void init_colorPairs() {
    //fare paring color dark green 
    init_color(COLOR_DARK_GREEN, 75,378, 154 );
    init_pair(1, COLOR_GREEN,  COLOR_GREEN);   // green
    init_pair(2, COLOR_WHITE,  COLOR_WHITE);     // White
    init_pair(3, COLOR_BLACK,  COLOR_BLACK);     // Black (for details like eyes)
    init_pair(4, COLOR_RED,    COLOR_RED);       // red 
    init_pair(5, COLOR_DARK_GREEN, COLOR_DARK_GREEN);
    init_pair(6, COLOR_BLACK, COLOR_DARK_GREEN);
    init_pair(7, COLOR_BLACK, COLOR_GREEN);
}


void drawShape(int originY, int originX, int height, int width, const int shape[][SNAKE_HEAD_W]) { //snake head
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int colorIndex = shape[row][col];
            if (colorIndex != 0) {
                attron(COLOR_PAIR(colorIndex));
                mvaddch(originY + row, originX + col, ' ');
                attroff(COLOR_PAIR(colorIndex));
            }
        }
    }
}

void drawShape2(int originY, int originX, int height, int width, const int shape[][SNAKE_BODY_W]) { //snake body
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int colorIndex = shape[row][col];
            if (colorIndex != 0) {
                attron(COLOR_PAIR(colorIndex));
                mvaddch(originY + row, originX + col, ' ');
                attroff(COLOR_PAIR(colorIndex));
            }
        }
    }
}


void drawSnake(int originY, int originX, int numBodySegments) {
    // testa snake
    drawShape(originY-2, originX+3, SNAKE_HEAD_H, SNAKE_HEAD_W, SNAKE_HEAD);

    // corpo a dx adiacente al precedente 
    int seg_originX = originX + SNAKE_HEAD_W; // inizia dopo la testa
    for (int i = 0; i < numBodySegments; i++) {
        drawShape2(originY, seg_originX, SNAKE_BODY_H, SNAKE_BODY_W, SNAKE_BODY);
        seg_originX += SNAKE_BODY_W; 
    }
}

void repaintAll(int max_x, int max_y, int selected){
    
    for (int i = 0; i < 3; i++) {
        int pair_id = (i == selected ? 5 : 1);
        drawFilledCircle(windArr[i].posY, windArr[i].posX, RADIUS_CIRCLE_X, RADIUS_CIRCLE_Y, pair_id);
    }
    

    attron(COLOR_PAIR(selected == 1 ? 6 : 7));
    int textLen = strlen(" _____ __    _____ __ __");

    move(max_y/2-2, max_x/2-textLen/2);
    printw(" _____ __    _____ __ __");
    move(max_y/2-1, max_x/2-textLen/2);
    printw("|  _  |  |  |  _  |  |  |");
    move(max_y/2, max_x/2-textLen/2);
    printw("|   __|  |__|     |_   _|");
    move(max_y/2+1, max_x/2-textLen/2); 
    printw("|__|  |_____|__|__| |_|");

    attroff(COLOR_PAIR(selected == 2 ? 6 : 7));

    refresh();

}

void drawVerticalSnake(int startY) {
    const int LETTERS = 5;
    const int H = 5, W = 5;
    const int SPACING = 1;  //tra una lettera e l'altra

    static const int pattern[LETTERS][H][W] = {
      // S
      {{1,1,1,1,1},
       {1,0,0,0,0},
       {1,1,1,1,0},
       {0,0,0,0,1},
       {1,1,1,1,1}},
      // N
      {{1,0,0,0,1},
       {1,1,0,0,1},
       {1,0,1,0,1},
       {1,0,0,1,1},
       {1,0,0,0,1}},
      // A
      {{0,1,1,1,0},
       {1,0,0,0,1},
       {1,1,1,1,1},
       {1,0,0,0,1},
       {1,0,0,0,1}},
      // K
      {{1,0,0,0,1},
       {1,0,0,1,0},
       {1,1,1,0,0},
       {1,0,0,1,0},
       {1,0,0,0,1}},
      // E
      {{1,1,1,1,1},
       {1,0,0,0,0},
       {1,1,1,1,0},
       {1,0,0,0,0},
       {1,1,1,1,1}}
    };

    attron(COLOR_PAIR(1));
    for (int L = 0; L < LETTERS; L++) {
        int baseY = startY + L * (H + SPACING);
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                if (pattern[L][r][c]) {
                    mvaddch(baseY + r, 1 + c, ACS_BLOCK);
                }
            }
        }
    }
    attron(COLOR_PAIR(2));

}

void page(int max_x,int max_y){
    keypad(stdscr, TRUE);

    int c; //getch of the button pressd 
    int numchoice = 0;

    int numSegments = (max_x/3)/SNAKE_BODY_W-1;

    int totalSnakeWidth = SNAKE_HEAD_W + numSegments * SNAKE_BODY_W;
    
    int originX = (max_x - totalSnakeWidth) ;
    int originY = windArr[numchoice].posY +1;

    drawSnake(originY, originX, numSegments);
    drawVerticalSnake((max_y < 32) ? 1 : max_y/2-16);   

    repaintAll(max_x, max_y, numchoice);
    bool cont = true;
    while ((c = getch()) != 27) {
        switch (c) {
            case KEY_UP :
                if(numchoice == 1 || numchoice == 2){
                    numchoice --;
                    originY = windArr[numchoice].posY - 2 ;
                }
            break;
            case KEY_DOWN :
                if(numchoice == 0 || numchoice == 1 || numchoice < 0){
                    numchoice ++;
                    originY = windArr[numchoice].posY- 2;
                }
            break;
            case '\n' : 
                switch (numchoice) {
                    case 0: 
                    break;
                    case 1:
                        cont = false;
                    break; 
                    case 2:
                    break; 
                    default:
                    break;
                }
            break;
        }
        clear();
        refresh();
        if(!cont) break;
        repaintAll(max_x, max_y,numchoice);
        drawSnake(originY, originX, numSegments);
        
        drawVerticalSnake((max_y < 32) ? 1 : max_y/2-16);   
    }
}


void initPage(int max_x,int max_y){

    init_colorPairs();
    attron(COLOR_PAIR(7));
    int textLen = strlen(" _____ __    _____ __ __");

    move(max_y/2-2, max_x/2-textLen/2);
    printw(" _____ __    _____ __ __");
    move(max_y/2-1, max_x/2-textLen/2);
    printw("|  _  |  |  |  _  |  |  |");
    move(max_y/2, max_x/2-textLen/2);
    printw("|   __|  |__|     |_   _|");
    move(max_y/2+1, max_x/2-textLen/2); 
    printw("|__|  |_____|__|__| |_|");

    attroff(COLOR_PAIR(7));

    windArr[0] = {(int)(max_y*0.2),max_x/2};
    windArr[1] = {(int)(max_y*0.5),max_x/2};
    windArr[2] = {(int)(max_y*0.8),max_x/2};

}


WINDOW* mainPage(){
    
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x); // Get screen size
    WINDOW* ret = new_bordered_window(max_y , max_x , 0,0);

    start_color();          // attivare colori

    initPage(max_x, max_y);
    page(max_x,max_y);
     
    return ret;
}