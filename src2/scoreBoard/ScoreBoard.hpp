#ifndef SCORE_BOARD_HPP
#define SCORE_BOARD_HPP

#include <fstream>
#include <vector>


using namespace std;

struct DataPlayer{
    char name[4];
    int score;
};

struct Scoreboard {
    DataPlayer levelScores[30][5];
};

void serialize(Scoreboard scoreboard);
void deserialize(Scoreboard*scoreboard);
void saveScore(int level, DataPlayer score, Scoreboard*scoreboard);

void printData(Scoreboard scoreboard);

#endif