#include "ScoreBoard.hpp"
#include <cstdio>
#include <cstring>
#include <ncurses.h>

void scoreBoard::serialize(scoreBoard scoreboard) {
    ofstream out("scoreboard", ios::binary);
    out.write((char*)(char*)(&scoreboard), sizeof(levelScores));
    out.close();
}

void scoreBoard::deserialize(scoreBoard*scoreboard) {
    ifstream in("scoreboard", ios::binary);
    char*buf = (char*)scoreboard;
    in.read(buf, sizeof(levelScores));
    in.close();
}


void scoreBoard::saveScore(int level, DataPlayer score, scoreBoard*scoreboard) {
    score.name[3] = '\0';

    DataPlayer* top = scoreboard->levelScores[level];
    int pos = 10;
    for (int i = 0; i < 10; ++i) {
        bool emptySlot = (top[i].name[0] == '\0' && top[i].score == 0);

        if (emptySlot || score.score > top[i].score) {
            pos = i;
            break;
        }
    }

    if (pos >= 10) {
        return;
    }

    for (int j = 9; j > pos; --j) {
        top[j] = top[j - 1];
    }

    top[pos] = score;
}


void scoreBoard::printData(scoreBoard scoreboard, int level, WINDOW* win) {
    if (!win) return;

    box(win, 0, 0);

    int h, w;
    getmaxyx(win, h, w);

    // titolo centrato
    char title[64];
    std::snprintf(title, sizeof(title), " LEVEL %d SCORES ", level);
    int title_x = (w - (int)std::strlen(title)) / 2;
    if (title_x < 1) title_x = 1;
    mvwprintw(win, 3, title_x, "%s", title);

    const int left   = 2;
    const int rank_c = left;
    const int name_c = left + 6;
    const int score_c = w - 10;

    // header
    mvwprintw(win, 5, rank_c,  "RANK");
    mvwprintw(win, 5, name_c,  "NAME");
    mvwprintw(win, 5, score_c, "SCORE");

    // riga orizzontale sotto l'header
    mvwhline(win, 6, 1, 0, w - 2);

    for (int i = 0; i < 10; ++i) {
        const DataPlayer& p = scoreboard.levelScores[level][i];

        const char* name = (p.name[0] ? p.name : "---");

        int row = 8 + i;

        mvwprintw(win, row, rank_c,  "%d.", i + 1);
        mvwprintw(win, row, name_c,  "%-3.3s", name);   // tanto e' sempre max 3 char di nome

        mvwprintw(win, row, score_c, "%6d", p.score);
    }

    wrefresh(win);
}

void scoreBoard::openScoreBoard(scoreBoard scoreboard, int width, int height) {
    int y = getmaxy(stdscr)/2-height/2;
    int x = getmaxx(stdscr)/2-width/2;

    WINDOW* win = newwin(height, width, y, x);
    keypad(win, TRUE);
    curs_set(0);

    int currentLevel = 0;

    while(true) {
        werase(win);
        box(win, 0, 0);
        mvwprintw(win, 1, 2, "<- Prev | Next ->  |  q: Quit   |  Level: %d/29", currentLevel);
        scoreBoard::printData(scoreboard, currentLevel, win);
        wrefresh(win);

        int ch = wgetch(win);
        if(ch == 'q' || ch == 'Q') break;
        if(ch == KEY_LEFT && currentLevel > 0) currentLevel--;
        if(ch == KEY_RIGHT && currentLevel < 29) currentLevel++;
    }

    delwin(win);
}

