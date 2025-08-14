#include "ScoreBoard.hpp"
#include <cstdio>
#include <ncurses.h>
#include <string>
#include <system_error>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void serialize(Scoreboard scoreboard) {
    ofstream out("scoreboard", ios::binary);
    for(int i = 0; i < sizeof(Scoreboard); i++) {
        char *s = (char*)(&scoreboard)+i;
        out.write((char*)s, 1);
        //printf("%x ", (char)*s);
    }
    out.close();
}

void deserialize(Scoreboard*scoreboard) {
    ifstream in("scoreboard", ios::binary);
    char*buf = (char*)scoreboard;
    in.read(buf, sizeof(Scoreboard));
    in.close();
}


void saveScore(int level, DataPlayer score, Scoreboard*scoreboard) {
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


void printData(Scoreboard scoreboard, int level, WINDOW* win){
    wclear(win);
    box(win, 0, 0);
    int max_x = getmaxx(stdscr);
    int max_y = getmaxy(stdscr);

    mvwprintw(win,max_y*0.1, max_x/2, "LEVEL %d SCORES",level );

    for(int i = 4; i >= 0; i--){
        mvwprintw(win, (max_y*(0.2*i)), max_x/2, "%s : %d", scoreboard.levelScores[level][i].name,scoreboard.levelScores[level][i].score );
    }

}

void printScoreBoard(Scoreboard scoreboard, WINDOW* win){
    char c = getch();
    int level = 0;
    while (c != 'x') {
        switch (c) {
            case KEY_LEFT:
            level -= (level > 0) ? 1 : 0;
            break;
            case KEY_RIGHT:
            level += (level < 29) ? 1 : 0;
            break;
            default:
            break;
        }
        printData(scoreboard, level, win);
    }
}

/*vector<DataPlayer> readFile(const string& filename) {
    vector<DataPlayer> players;
    ifstream file(filename);

    if (!file.is_open()) {
        return players;
    }

    string line;
    // Scarta la riga di intestazione
    getline(file, line);

    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);

        if (pos1 == string::npos || pos2 == string::npos)
            continue; // Riga malformata

        string name = line.substr(0, pos1);
        string levelStr = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string scoreStr = line.substr(pos2 + 1);

        try {
            DataPlayer p;
            p.name = name;
            p.lvl = stoi(levelStr);
            p.score = stoi(scoreStr);
            players.push_back(p);
        } catch (const exception& e) {
        }
    }

    file.close();
    return players;
}

void appendFile(const string& filename, DataPlayer data){
    ofstream file("filename", ios::app);

    if(!file.is_open()){
        return;
    }

    file << data.name << "," << data.lvl << "," << data.score << "\n";
    file.close();
}


bool deleteData(const string &filename, DataPlayer data) {
    ifstream infile(filename);
    if (!infile.is_open()) return false;

    vector<string> lines;
    string line;
    bool deleted = false;

    while (getline(infile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);

        if (pos1 == string::npos || pos2 == string::npos) {
            lines.push_back(line); // Riga malformata, la teniamo
            continue;
        }

        string name = line.substr(0, pos1);
        string levelStr = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string scoreStr = line.substr(pos2 + 1);

        if (name == data.name &&
            levelStr == to_string(data.lvl) &&
            scoreStr == to_string(data.score)) {
            deleted = true; // Record trovato, lo saltiamo (non lo aggiungiamo)
        } else {
            lines.push_back(line); // Lo teniamo
        }
    }

    infile.close();

    if (!deleted) return false; // Nessun record eliminato

    ofstream outfile(filename, ios::trunc); // Sovrascrive il file
    if (!outfile.is_open()) return false;

    for (const auto &l : lines) {
        outfile << l << '\n';
    }

    outfile.close();
    return true;
}*/



// for (DataPlayer dp : players) {
// if (!players.empty() && data.score >= players.back().score) {
//     players.pop_back();  // elimina l'ultimo elemento
//     }
//         break;
// }