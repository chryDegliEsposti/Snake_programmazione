#include "levelGraphics.hpp"
#include "graphicFuncs.hpp"
#include "mainMenu.hpp"
#include <algorithm>
#include <cstddef>
#include <ncurses.h>
#include "../debug/print.hpp"

#define maxLev 100
const static int RADIUS_CIRCLE_X = 15;
const static int RADIUS_CIRCLE_Y = 3;

//WINDOW *my_pad = newpad(righe_totali, colonne_totali); TODO: usare questo per la finesgtra scorrevole

levelGraphics::levelGraphics(){
    getmaxyx(stdscr, this->maxy, this->maxx);
    this->l = new levels(maxLev);
}

levelGraphics::~levelGraphics() {
    delete this->l;
}

void levelGraphics::level() {
    //clear();
    
    levels::level *currLev;
    int levelHeight = RADIUS_CIRCLE_Y*2;   // Altezza in righe di un livello
    WINDOW *my_pad = newpad((maxy/10)*maxLev*(maxLev+1), maxx); //formua sommatoria di i = 0 a n = n*(n+1)/2

    // Disegno tutti i livelli nel pad
    for (int i = 1; i <= maxLev; i++) {
        //dbg::print_debug_hell_yeah("I: %d",i);
        currLev = this->l->goToLevel(i);
        if (!currLev) continue;
        drawFilledCircleWin(my_pad,i * levelHeight, maxx / 2, RADIUS_CIRCLE_X, RADIUS_CIRCLE_Y, 1);

        wattron(my_pad,COLOR_PAIR(7));
        mvwprintw(my_pad, i * levelHeight - 1, maxx/2 - 4, "level: %d", currLev->num);
        mvwprintw(my_pad, i * levelHeight,     maxx/2 - 8, "speed : %d lenght: %d",
                  currLev->vel, currLev->snakelen);
    }
    wattroff(my_pad, COLOR_PAIR(7));

    int c;
    int levelCounter = 1;
    int pad_top = 0;  // offset verticale del pad

    currLev = l->goToLevel(levelCounter);

    // Mostra inizialmente
    prefresh(my_pad, pad_top, 0, 0, 0, maxy-1, maxx-1);

    int selectedY = levelCounter * levelHeight; 


    while ((c = getch()) != 'x') {

        drawFilledCircleWin(my_pad, selectedY, maxx/2, RADIUS_CIRCLE_X, RADIUS_CIRCLE_Y, 1);
        wattron(my_pad, COLOR_PAIR(7));
        mvwprintw(my_pad, selectedY - 1, maxx/2 - 4, "level: %d", currLev->num);
        mvwprintw(my_pad, selectedY,     maxx/2 - 8, "speed : %d lenght: %d",
                  currLev->vel, currLev->snakelen);
        wattroff(my_pad, COLOR_PAIR(7));

        switch (c) {
            case KEY_DOWN:
                if (levelCounter < maxLev) levelCounter++;
                break;
            case KEY_UP:
                if (levelCounter > 1) levelCounter--;
                break;
            case '\n':
                // TODO: azione sul livello selezionato
                break;
        }

        // aggiorno il livello corrente
        currLev = l->goToLevel(levelCounter);

        // calcolo la riga del livello selezionato nel pad
        selectedY = levelCounter * levelHeight; 

        // Se il livello scende sotto lo schermo aloora scrolla giù
        if (selectedY - pad_top > maxy - 5) {
            pad_top = selectedY - maxy + 5;
        }
        // Se il livello sale sopra lo schermo allora scrolla su
        else if (selectedY < pad_top + 5) {
            pad_top = selectedY - 5;
            if (pad_top < 0) pad_top = 0;
        }

        // Ridisegno il livello selezionato evidenziato
        drawFilledCircleWin(my_pad, selectedY, maxx/2, RADIUS_CIRCLE_X, RADIUS_CIRCLE_Y, 5);
        wattron(my_pad, COLOR_PAIR(6));
        mvwprintw(my_pad, selectedY - 1, maxx/2 - 4, "level: %d", currLev->num);
        mvwprintw(my_pad, selectedY,     maxx/2 - 8, "speed : %d lenght: %d",
                  currLev->vel, currLev->snakelen);
        wattroff(my_pad, COLOR_PAIR(6));

        // Refresh della finestra visibile del pad
        prefresh(my_pad, pad_top, 0, 0, 0, maxy-1, maxx-1);
    }
}
