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

    WINDOW* setBoard(int width, int height);
    scoreBoard::DataPlayer gameOver(WINDOW* win);
    bool GameLoop(WINDOW* win);

    private: 
    char inputAndMove(Snake*snake);
    bool checkTimer(int gameStartMillis);
    bool run(WINDOW*win);
};



#endif