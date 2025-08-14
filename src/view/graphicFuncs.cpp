
#include "graphicFuncs.hpp"

using namespace std;

void init(){
    initscr();
    cbreak(); //serve per disabilitare "terminal line buffering"
    noecho(); //previene l'eco tra caratteri
    curs_set(0); //visibilità schermo
}


WINDOW *new_bordered_window(int height, int width, int y, int x) {
    WINDOW *window = newwin(height, width, y, x);
    box(window, 0, 0);
    wrefresh(window);
    return window;
}

void drawFilledCircle(int center_y, int center_x, int radius_x, int radius_y,int color) {
    attron(COLOR_PAIR(color));  //per settare il colore

        for (int y = center_y - radius_y; y <= center_y + radius_y; y++) {
            for (int x = center_x - radius_x; x <= center_x + radius_x; x++) {
                //formula utilizzata = (x-x_center)^2/radius_x^2 + (y-y_center)^2/radius_y^2 >= 1 (formula ellisse)
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

/*



*/