#include "view/mainMenu.hpp"
#include "game/Game.hpp"
#include "scoreBoard/ScoreBoard.hpp"
#include "Levels/levels.hpp"
#include "view/mainMenu.hpp"
#include "scoreBoard/ScoreBoard.hpp"

#include <cstring>
#include <ncurses.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ctime>

int main(int, char**){
    srand(time(NULL));
    init();
    
    int choise = mainMenu::mainPage();

    while(choise != -1){
        
        if(choise == 0){
            WINDOW*score = newwin(getmaxy(stdscr)*0.8,getmaxx(stdscr)*0.8, getmaxy(stdscr)*0.1,getmaxx(stdscr)*0.1);
            wrefresh(score);
            // scoreBoard s;
            // memset(&s, 0x00, sizeof(scoreBoard));
            // scoreBoard::DataPlayer p1 {"chr",2};
            // scoreBoard::DataPlayer p2 {"ddd",5};
            // scoreBoard::DataPlayer p3 {"sss",6};
            // scoreBoard::DataPlayer p4{"cri",7};
            // scoreBoard::DataPlayer p5 {"cnn",2};
            // scoreBoard::saveScore(0, p1, &s);
            // scoreBoard::saveScore(0, p2, &s);
            // scoreBoard::saveScore(0, p3, &s);
            // scoreBoard::saveScore(0, p4,  &s);
            // scoreBoard::saveScore(0, p5,  &s);
            // scoreBoard::serialize(s);
            scoreBoard s2;
            //memset(&s2, 0x00, sizeof(scoreBoard));
            scoreBoard::deserialize(&s2);
            attroff(COLOR_PAIR(2));
            scoreBoard::printData(s2,0,score);
        }
        if(choise == 1){
            Game game;
            int start = game.getMillis();
            WINDOW*win = game.setBoard();
            game.run(win, start);
            scoreBoard::DataPlayer dp = game.gameOver(win);
            scoreBoard toSerialize;
            scoreBoard::saveScore(0, dp, &toSerialize);
            scoreBoard::serialize(toSerialize);
        }if(choise == 2){
            //TODO : implementare scelta livelli
        }

        choise = mainMenu::mainPage();
    }


    endwin();

    // clear();
    // wclear(win);
    // wrefresh(win);
    // refresh();

    // mvwprintw(win, 50, 50, "boiode de dio can");

    // getch();
    
    //mvwprintw(win, getmaxy(win) / 2, (getmaxx(win) - strlen(text)) / 2, "%s", text); -- nella window
    
    return 0;
}

/*


*/