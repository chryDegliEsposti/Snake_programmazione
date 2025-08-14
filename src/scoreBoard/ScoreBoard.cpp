#include "ScoreBoard.hpp"
#include <cstdio>
#include <ncurses.h>

void scoreBoard::serialize(scoreBoard scoreboard) {
    ofstream out("scoreboard", ios::binary);
    for(int i = 0; i < sizeof(levelScores); i++) {
        char *s = (char*)(&scoreboard)+i;
        out.write((char*)s, 1);
        //printf("%x ", (char)*s);
    }
    out.close();
}

void scoreBoard::deserialize(scoreBoard*scoreboard) {
    ifstream in("scoreboard", ios::binary);
    char*buf = (char*)scoreboard;
    in.read(buf, sizeof(levelScores));
    in.close();
}


void scoreBoard::saveScore(int level, DataPlayer score, scoreBoard*scoreboard) {
    DataPlayer tmp[6];
    memset(&tmp, 0x00, sizeof(DataPlayer)*6);
    DataPlayer t;
    memset(&t, 0x00, sizeof(DataPlayer));
    memcpy(tmp + 1, (*scoreboard).levelScores[level], sizeof(DataPlayer) * 5);
    for(int i = 0; i < 5; i++) {
        if(tmp[i+1].score < score.score) {
            memcpy(&tmp[i], &score, sizeof(DataPlayer));
            break;
        }
        memcpy(&t, &tmp[i+1], sizeof(DataPlayer));
        memcpy(&tmp[i+1], &tmp[i], sizeof(DataPlayer));
        memcpy(&tmp[i], &t, sizeof(DataPlayer));
    }
    memcpy((*scoreboard).levelScores[level], tmp, sizeof(DataPlayer)*5);
}


void scoreBoard::printData(scoreBoard scoreboard, int level, WINDOW* win){
    
    box(win, 0, 0);
    wrefresh(win);
    int max_x = getmaxx(stdscr);
    int max_y = getmaxy(stdscr);

    double scoreboardWidth = 7;
    double winHeight = getmaxy(win);
    double scoreboardHeight = winHeight*0.85;
    double winWidth = getmaxx(win);

    double x = winWidth/2 - scoreboardWidth/2;
    double y = winHeight/2 - scoreboardHeight/2;

    attroff(COLOR_PAIR(2));

    mvwprintw(stdscr,max_y*0.1, max_x/2, "LEVEL %d SCORES",level );

    for(int i = 4; i >= 0; i--){
        mvwprintw(win, y*((i+1)*(scoreboardHeight/12)), x, "%s : %d", scoreboard.levelScores[level][i].name,scoreboard.levelScores[level][i].score );
        wrefresh(win);
    }
    
    refresh();
    getch();

}

scoreBoard* scoreBoard::nextPage(scoreBoard *curr) {
    if(curr->next) {
        scoreBoard* tmp = curr;
        curr = curr->next;
        curr->before = tmp;
        curr->id++;
        return curr;
    }
    return curr;
}

scoreBoard* scoreBoard::beforePage(scoreBoard *curr) {
    if(curr->before) {
        scoreBoard* tmp = curr;
        curr = curr->before;
        curr->next = tmp;
        curr->id--;
        return curr;
    }
    return curr;
}

void scoreBoard::openScoreBoard(scoreBoard* startPage) {
    scoreBoard* curr = startPage;

    int ch;
    WINDOW* win = newwin(20, 50, 5, 10);
    keypad(win, TRUE);  //abilita i tasti (freccie)
    curs_set(0);        //nasconde il cursore

    while(true) {
        werase(win);
        scoreBoard::printData(*curr, curr->id, win);
        box(win, 0, 0);
        mvwprintw(win, 1, 2, "<- Prev | Next ->  |  q: Quit");
        wrefresh(win);

        ch = wgetch(win);
        
        if(ch == 'q' || ch == 'Q') {break;}

        if(ch == KEY_LEFT && curr->before) {
            beforePage(curr);
        }

        if(ch == KEY_RIGHT && curr->next) {
            nextPage(curr);
        }
    }

    delwin(win);
}

