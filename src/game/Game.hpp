#ifndef GAME_HPP
#define GAME_HPP

#include <cstdint>
#include <ncurses.h>
#include <cstring>
#include <ncurses.h>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <ctime>
#include "Snake.hpp"
#include "Snake.hpp"
#include <cstring>
#include <ncurses.h>

#include "../scoreBoard/ScoreBoard.hpp"
#include "../Levels/levels.hpp"

class Game{
public:
    // ⇨ passa il livello corrente (può essere nullptr; gestiamo default)
    explicit Game(const levels::level* levelCfg);

    char lastInput = 'd';

    const uint64_t MAX_TIME = 300000;

    Snake snake;
    int max_x, max_y;
    int width, height, score;

    // info livello
    const levels::level* levelCfg = nullptr; // non-owning
    int  currentLevelNum = 1;
    int  tickMs = 500;       // velocità di gioco derivata da levelCfg->vel
    float bonusMult = 1.0f;  // moltiplicatore punteggio da levelCfg->bonus

    WINDOW* setBoard(int width, int height);
    scoreBoard::DataPlayer gameOver(WINDOW* win);
    bool GameLoop(WINDOW* win, WINDOW* coverBox);
    static void PauseGame(WINDOW* win);
    void mainMenuHandler(levels::level* currentLevel,levels lvlList);

private:
    // timeout di input dipende dal livello
    char getInput();
    char inputAndMove(Snake* snake, WINDOW* win);
    bool checkTimer(int gameStartMillis,WINDOW* coverBox);
    bool run(WINDOW* win);
};

#endif