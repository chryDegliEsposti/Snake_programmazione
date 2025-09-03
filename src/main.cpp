#include "view/mainMenu.hpp"
#include "game/Game.hpp"
#include "scoreBoard/ScoreBoard.hpp"
#include "Levels/levels.hpp"
#include "view/mainMenu.hpp"
#include "scoreBoard/ScoreBoard.hpp"
#include "view/levelGraphics.hpp"

#include <cstring>
#include <ncurses.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ctime>
#include <iostream>

static scoreBoard::DataPlayer makeP(const char* n, int s) {
    scoreBoard::DataPlayer p{};
    std::strncpy(p.name, n, 3);
    p.name[3] = '\0';
    p.score = s;
    return p;
}

void fillScoreboardWithDummyData() {
    scoreBoard sb{};
    for (int lvl = 0; lvl < 30; ++lvl) {
        for (int i = 0; i < 10; ++i) {
            char name[4] = { char('A' + (lvl % 26)), char('0' + i), '\0', '\0' };
            int sc = (lvl+1) * 1000 - i*50;
            scoreBoard::saveScore(lvl, makeP(name, sc), &sb);
        }
    }
    scoreBoard::serialize(sb);
}

int main(int, char**){

    // cri: niente sta roba e' per il debugger. potete toglierla se volete
    std::cout << "PID: " << getpid() << "\n";
    std::cin.get();



    srand(time(NULL));
    init();
    
    int choice = mainMenu::mainPage(); 

    while(choice != -1){
        
        if(choice == 0){
            scoreBoard sb{};
            scoreBoard::deserialize(&sb);
            scoreBoard::openScoreBoard(sb, 50, 20);
        }
        if(choice == 1){  
            Game game;
            WINDOW*win = game.setBoard(76, 24);
            game.GameLoop(win);
            /*scoreBoard::DataPlayer dp = game.gameOver(win);
            scoreBoard toSerialize;
            scoreBoard::saveScore(0, dp, &toSerialize);
            scoreBoard::serialize(toSerialize);*/
        }if(choice == 2){
            levelGraphics *l = new levelGraphics();
            l->level();
        }   

        choice = mainMenu::mainPage();
    }


    endwin();

    return 0;
}

/*


*/