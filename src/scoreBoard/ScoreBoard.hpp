#ifndef SCORE_BOARD_HPP
#define SCORE_BOARD_HPP

#include <fstream>
#include <cstdio>
#include <ncurses.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


using namespace std;

class scoreBoard {
    
    public:

    struct DataPlayer{
        char name[4];
        int score;
    };
    DataPlayer levelScores[30][10];


    static void serialize(scoreBoard scoreboard);
    static void deserialize(scoreBoard*scoreboard);
    static void saveScore(int level, DataPlayer score, scoreBoard*scoreboard);
    static void printData(scoreBoard scoreboard, int level, WINDOW* win);
    static void openScoreBoard(scoreBoard startPage, int width, int height);

    private:

};


#endif