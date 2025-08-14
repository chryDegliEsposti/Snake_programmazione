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
    Game();
    const uint64_t MAX_TIME = 300000;
    Snake snake;
    int max_x,max_y;
    int width, height,score;

    void run(WINDOW*win,int start);
    WINDOW* setBoard();
    int getMillis() ;
    scoreBoard::DataPlayer gameOver(WINDOW* win);

    private: 
    bool GameLoop(WINDOW* win, int gameStartMillis);
    char getInput(WINDOW*win);
};



#endif