#include "view/graphicFuncs.hpp"
#include "view/mainMenu.hpp"
#include "Game/GameBoard.hpp"

#include <cstring>
#include <ncurses.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ctime>
#include <string>
#include <fstream>
#include "scoreBoard/ScoreBoard.hpp"







int main(int, char**){

    srand(time(NULL));
    init();
    mainPage();

    startGame();



    // clear();
    // wclear(win);
    // wrefresh(win);
    // refresh();

    // echo();
    // mvwprintw(win, 20, 20, "inserire il tuo nome da frocio: ");
    // char str[100];
    // flushinp();    
    // wgetstr(win,str); 
    // wprintw(win,"\nHai scritto: %s", str);
    // wrefresh(win);

    // Scoreboard s;
    // memset(&s, 0x00, sizeof(Scoreboard));

    // DataPlayer p;
    // strncpy(p.name, str, 3);
    // p.name[3] = 0x00;

    // p.score = score;
    // saveScore(0, p, &s);
    // serialize(s);

    // wgetch(win);
    // //mvwprintw(win, getmaxy(win) / 2, (getmaxx(win) - strlen(text)) / 2, "%s", text); -- nella window
    // endwin();
    return 0;
}

/*


*/