
#include "graphicFuncs.hpp"
#include <ncurses.h>

using namespace std;

void init(){
    initscr();
    cbreak();
    noecho(); // non riscrive cio' che premi sul terminale
    curs_set(0); //visibilità schermo
}


WINDOW *new_bordered_window(int height, int width, int y, int x) {
    WINDOW *window = newwin(height, width, y, x);
    wrefresh(window);
    return window;
}

void drawFilledCircle(int center_y, int center_x, int radius_x, int radius_y,int color) {
    attron(COLOR_PAIR(color));  //per settare il colore

        for (int y = center_y - radius_y; y <= center_y + radius_y; y++) {
            for (int x = center_x - radius_x; x <= center_x + radius_x; x++) {
                // formula usata: (x-x_center)^2/radius_x^2 + (y-y_center)^2/radius_y^2 >= 1 (formula dell'ellisse)
                double dx = x - center_x;
                double dy = y - center_y;

                if ((dx * dx) / (radius_x * radius_x) + 
                    (dy * dy) / (radius_y * radius_y) < 1.0) {
                    
                    mvaddch(y, x, ACS_BLOCK); 
                }
            }
        }
        attroff(COLOR_PAIR(color));
}

void drawFilledCircleWin(WINDOW* win, int center_y, int center_x, int radius_x, int radius_y,int color) {
    wattron(win, COLOR_PAIR(color));  //per settare il colore

        for (int y = center_y - radius_y; y <= center_y + radius_y; y++) {
            for (int x = center_x - radius_x; x <= center_x + radius_x; x++) {
                // formula usata: (x-x_center)^2/radius_x^2 + (y-y_center)^2/radius_y^2 >= 1 (formula dell'ellisse)
                double dx = x - center_x;
                double dy = y - center_y;

                if ((dx * dx) / (radius_x * radius_x) + 
                    (dy * dy) / (radius_y * radius_y) < 1.0) {
                    
                    mvwaddch(win, y, x, ACS_BLOCK); 
                }
            }
        }
        wattroff(win, COLOR_PAIR(color));
}

/*



*/