#include "levelGraphics.hpp"
#include "graphicFuncs.hpp"
#include <algorithm>
#include <cstddef>
#include <ncurses.h>

#define maxLev 100
const static int RADIUS_CIRCLE_X = 15;
const static int RADIUS_CIRCLE_Y = 3;

//WINDOW *my_pad = newpad(righe_totali, colonne_totali); TODO: usare questo per la finesgtra scorrevole



levelGraphics::levelGraphics(){
    getmaxyx(stdscr, this->maxy, this->maxx);
    this->l = new levels(maxLev);
}

void levelGraphics::printLevel(levels::level *currLev){
    
}

void levelGraphics::level(){

    struct levelTracker{
        levels::level* level;
        bool selected[maxLev]{};
    };

    levelTracker *currLev;

    for (int i = 1; i <= maxLev; i++) {
        currLev->level = this->l->goToLevel(i);

        drawFilledCircle(5+i*(maxy/5), maxx/2, RADIUS_CIRCLE_X  , RADIUS_CIRCLE_Y, COLOR_GREEN);
        mvwprintw(stdscr, 5+i*(maxy/5)-2, maxx/2-4, "level: %d",currLev->level->num);                              //TODO: creare window per levels
        mvwprintw(stdscr, 5+i*(maxy/5), maxx/2-8, "speed : %d lenght: %d",currLev->level->vel, currLev->level->snakelen); //TODO: creare window per levels

    }

    int c;
    int levelCounter = 1;
    while ((c = getch()) != 'x') {
        currLev->selected[levelCounter] = false;

        switch (c) {
            case KEY_DOWN:
                if(levelCounter > 1)levelCounter++;
            break;
            case KEY_UP:
                if(levelCounter < maxLev) levelCounter--;
            break;
            case '\n':

            break;
        }
        currLev->selected[levelCounter] = true;


    }
}