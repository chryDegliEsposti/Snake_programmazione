#include "levelGraphics.hpp"
#include "graphicFuncs.hpp"
#include "mainMenu.hpp"
#include <algorithm>
#include <ncurses.h>

#define maxLev 30
static const int RADIUS_CIRCLE_X = 15;
static const int RADIUS_CIRCLE_Y = 3;

levelGraphics::levelGraphics(levels& lvls) : l(&lvls) {
    getmaxyx(stdscr, this->maxy, this->maxx);
}

levels* levelGraphics::getLevelsList() {
    return l;
}

levels::level* levelGraphics::selectLevel() {
    
    const int levelHeight = RADIUS_CIRCLE_Y * 2 + 2;
    const int pad_h = std::max(maxy, levelHeight * l->size() + 2);
    WINDOW* my_pad = newpad(pad_h, maxx);
    int i = 1;

    for (levels::level* node = l->getHead(); node && i <= l->size(); node = node->next, ++i) {
        mvwprintw(my_pad, 4, maxx/10, "q : quit");
        int y = i * levelHeight;
        drawFilledCircleWin(my_pad, y, maxx/2, RADIUS_CIRCLE_X, RADIUS_CIRCLE_Y, 1);
        wattron(my_pad, COLOR_PAIR(7));
        mvwprintw(my_pad, y - 1, maxx/2 - 6, "level: %d", node->num);
        mvwprintw(my_pad, y,     maxx/2 - 10, "speed: %d  length: %d", node->vel, node->snakelen);
        wattroff(my_pad, COLOR_PAIR(7));
    }

    int c;
    int levelCounter = 1;

    int pad_top = 0;

    levels::level* currLev = l->goToLevel(levelCounter); // qui si', voglio aggiornare curr
    prefresh(my_pad, pad_top, 0, 0, 0, maxy - 1, maxx - 1);

    int selectedY = levelCounter * levelHeight;

    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE);

    while ((c = getch()) != 'q') {
        drawFilledCircleWin(my_pad, selectedY, maxx/2, RADIUS_CIRCLE_X, RADIUS_CIRCLE_Y, 1);
        wattron(my_pad, COLOR_PAIR(7));
        mvwprintw(my_pad, selectedY - 1, maxx/2 - 6, "level: %d", currLev->num);
        mvwprintw(my_pad, selectedY,     maxx/2 - 10, "speed: %d  length: %d", currLev->vel, currLev->snakelen);
        wattroff(my_pad, COLOR_PAIR(7));

        switch (c) {
            case KEY_DOWN: if (levelCounter < l->size()) ++levelCounter; break;
            case KEY_UP:   if (levelCounter > 1)          --levelCounter; break;
            case '\n':
                delwin(my_pad);
                return l->goToLevel(levelCounter);
        }

        currLev   = l->goToLevel(levelCounter);
        selectedY = levelCounter * levelHeight;

        // scrolling
        if (selectedY - pad_top > maxy - 5) {
            pad_top = selectedY - maxy + 5;
        } else if (selectedY < pad_top + 5) {
            pad_top = std::max(0, selectedY - 5);
        }

        // evidenziato
        drawFilledCircleWin(my_pad, selectedY, maxx/2, RADIUS_CIRCLE_X, RADIUS_CIRCLE_Y, 5);
        wattron(my_pad, COLOR_PAIR(6));
        mvwprintw(my_pad, selectedY - 1, maxx/2 - 6, "level: %d", currLev->num);
        mvwprintw(my_pad, selectedY,     maxx/2 - 10, "speed: %d  length: %d", currLev->vel, currLev->snakelen);
        wattroff(my_pad, COLOR_PAIR(6));

        prefresh(my_pad, pad_top, 0, 0, 0, maxy - 1, maxx - 1);
    }

    delwin(my_pad);
    return l->getCurrLevel(); // se esci con 'q', tieni l'ultimo selezionato
}
