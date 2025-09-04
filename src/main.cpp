#include "view/mainMenu.hpp"
#include "game/Game.hpp"
#include "scoreBoard/ScoreBoard.hpp"
#include "Levels/levels.hpp"
#include "view/levelGraphics.hpp"

#include <cstring>
#include <ncurses.h>
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
    p.score   = s;
    return p;
}

void fillScoreboardWithDummyData() {
    scoreBoard sb{};
    for (int lvl = 0; lvl < 30; ++lvl) {
        for (int i = 0; i < 10; ++i) {
            char name[4] = { char('A' + (lvl % 26)), char('0' + i), '\0', '\0' };
            int sc = (lvl + 1) * 1 - i * 50;
            scoreBoard::saveScore(lvl, makeP(name, sc), &sb);
        }
    }
    scoreBoard::serialize(sb);
}

int main(int, char**) {
    // debug
    std::cout << "PID: " << getpid() << "\n";
    // std::cin.get();

    // CREA qui la lista livelli e passala alla UI
    constexpr int kMaxLevels = 30;
    levels lvlList{kMaxLevels};
    levels::level* currentLevel = lvlList.goToLevel(1);

    srand(time(NULL));
    init();

    int choice = mainMenu::mainPage();
    Game game(0);

    while (choice != -1) {

        if (choice == 0) {
            fillScoreboardWithDummyData();
            scoreBoard sb{};
            scoreBoard::deserialize(&sb);
            scoreBoard::openScoreBoard(sb, 50, 20);
        }

        if (choice == 1) {
            int width = 76;
            int height = 24;
            int y = getmaxy(stdscr)/2-height/2;
            int x = getmaxx(stdscr)/2-width/2;

            Game game(currentLevel);
            WINDOW* blackCover = newwin(getmaxy(stdscr), width, 0, x);

            wrefresh(blackCover);
            WINDOW* win = game.setBoard(76, 24);
            game.GameLoop(win,blackCover);

            wclear(blackCover);
            
            scoreBoard::DataPlayer dp = game.gameOver(win);
            scoreBoard toSerialize;
            // usa currentLevel->num se vuoi salvare per livello
            scoreBoard::saveScore(currentLevel ? currentLevel->num - 1 : 0, dp, &toSerialize);
            scoreBoard::serialize(toSerialize);
        }

        if (choice == 2) {
            levelGraphics lg{lvlList};            // NON alloca livelli nuovi
            currentLevel = lg.selectLevel();      // scegli e mantieni il puntatore valido
            // qui puoi usare currentLevel->vel / snakelen per configurare il Game
        }

        choice = mainMenu::mainPage();
    }

    endwin();
    return 0;
}
