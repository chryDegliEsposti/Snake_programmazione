#include "Game.hpp"
#include <cstdint>
#include <fstream>
#include <iostream>
#include "../debug/print.hpp"

int getMillis() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return uint64_t(ts.tv_sec) * 1000 + ts.tv_nsec / 1000000;
}

Game::Game(): snake(3, 5, 5){
    this->score = 0;
}



WINDOW* Game::setBoard(int width, int height){
    int y = getmaxy(stdscr)/2-height/2;
    int x = getmaxx(stdscr)/2-width/2;
    this->width = width;
    this->height = height;
    WINDOW*win = newwin(height, width, y, x);
    
    snake.setParam(width, height);
    snake.initSnake();
    
    dbg::print_debug_hell_yeah("ora dopo l'init, controlliamo sta tail: x: ", snake.tail->x, "  y: ", snake.tail->y);

    box(win, 0,0);
    wrefresh(win);
    return win;
}

bool Game::run(WINDOW*win){
    dbg::print_debug_hell_yeah("gameloop");
        
    mvwprintw(win, snake.cibo->y, snake.cibo->x, "%c", snake.cibo->type);
    wrefresh(win);

    if(snake.x >= width-1 || snake.y >= height-1 || snake.x <= 0 || snake.y <= 0) {
        
        dbg::print_debug_hell_yeah("x=", snake.x, " y=", snake.y, " w=", width, " h=", height);
        snake.x = snake.head->x;
        snake.y = snake.head->y;
        return false;
    }
    
    Object* temp = snake.tail;

    do {
        dbg::print_debug_hell_yeah("checking tail ", " snake x: ", snake.x, ", snake y: ", snake.y, ". \ttail: ", " tail x: ", temp->x, ", tail y: ", temp->y);
        if(temp->next == nullptr) break;
        dbg::print_debug_hell_yeah("isnull ", temp->next->x); // TODO: bug sull'init del serpente imho
        if(temp->x == snake.x && temp->y == snake.y) {
            dbg::print_debug_hell_yeah("tailBitten", " snake x: ", snake.x, ", snake y: ", snake.y, ". \ttail: ", " tail x: ", temp->x, ", tail y: ", temp->y);
            snake.x = snake.head->x;
            snake.y = snake.head->y;
            return false;
        }
    } while((temp = temp->next) != nullptr);

    mvwprintw(win, snake.tail->y, snake.tail->x, " ");

    snake.head->next = snake.tail;

    snake.tail->x = snake.x;
    snake.tail->type = 'O';
    snake.tail->y = snake.y;

    snake.tail = snake.tail->next;          // salviamo nella nostra var tail, la nuova tail
    snake.head->next->next = nullptr; // tail vecchia non ha un piu un next

    snake.head->type = 'o';

    snake.head = snake.head->next;
    
    //wclear(win);
    //box(win, ':', '=');

    temp = snake.tail;
    do {
        mvwprintw(win, temp->y, temp->x, "%c", temp->type);
    } while((temp = temp->next) != nullptr);

    if(snake.head->x == snake.cibo->x && snake.head->y == snake.cibo->y) {
        snake.cibo->y = (int)(rand()%(height-2))+2;
        snake.cibo->x = (int)(rand()%(width-2))+2;
        score++;
    }

    wrefresh(win);

    return true;
}

char getInput() {
    int TIMEOUT = 500;
    int start = getMillis();
    char lastInput = ERR;
    timeout(0);
    int i = 0;
    while((getMillis() - start) <= TIMEOUT) {
        char temp = getch();
        if(temp != ERR)
            lastInput = temp;
    }
    return lastInput;
}

char Game::inputAndMove(Snake *snake) {
    static char last_chinput = 'd';

    char chinput = getInput();
    
    if(chinput == ERR) {
        chinput = last_chinput;
    }
    if(!snake->snake_move(chinput, &snake->y, &snake->x)) {
        snake->snake_move(last_chinput, &snake->y, &snake->x);
    } else last_chinput = chinput;

    return chinput;
}

bool Game::checkTimer(int gameStartMillis) {
    dbg::print_debug_hell_yeah("millis: ",getMillis());
    uint64_t elapsed = getMillis() - gameStartMillis;
    int remaining = MAX_TIME - elapsed;
    if(remaining < 0) remaining = 0;
    int mm = (remaining / 1000) / 60;
    int ss = (remaining / 1000) % 60;

    int y = getmaxy(stdscr)/2-height/2-1;
    mvwprintw(stdscr, y, getmaxx(stdscr)/2-width/2+2, "TIME : %02d:%02d", mm, ss);
    mvwprintw(stdscr, y, getmaxx(stdscr)/2-5, "SCORE : %d", score);
    mvwprintw(stdscr, y, getmaxx(stdscr)/2+width/2-12, "LEVEL : %d", 1);
    wrefresh(stdscr);

    if (getMillis() - gameStartMillis >= MAX_TIME) {// tempo scaduto
        dbg::print_debug_hell_yeah("timeout!");
        return false;
    }
    return true;
}

bool Game::GameLoop(WINDOW* win){
    attroff(COLOR_PAIR(2));
    while(1) {
        int gameStartMillis = getMillis();
        
        inputAndMove(&snake);

        if(!checkTimer(gameStartMillis)) return false;

        if(!run(win)) return false;
    }
}

scoreBoard::DataPlayer Game::gameOver(WINDOW* win){
    scoreBoard::DataPlayer dp;

    wclear(win);

    box(win, 0, 0);

    int textLen = strlen("    _____      ___      __  __  ______  ____ __      __ ______  _____  ");


    mvwprintw(win, getmaxy(win)/2-6, (getmaxx(win)/2)-(textLen/2), R"(   _____      ___      __  __  ______  ____ __      __ ______  _____   )");
    mvwprintw(win, getmaxy(win)/2-5, (getmaxx(win)/2)-(textLen/2), R"(  / ____|    /   \    |  \/  ||  ____|/ __ \\ \    / /|  ____||  __ \  )");
    mvwprintw(win, getmaxy(win)/2-4, (getmaxx(win)/2)-(textLen/2), R"( | |  __    /  ^  \   | \  / || |__  | |  | |\ \  / / | |__   | |__) | )");
    mvwprintw(win, getmaxy(win)/2-3, (getmaxx(win)/2)-(textLen/2), R"( | | |_ |  /  /_\  \  | |\/| ||  __| | |  | | \ \/ /  |  __|  |  _  /  )");
    mvwprintw(win, getmaxy(win)/2-2, (getmaxx(win)/2)-(textLen/2), R"( | |__| | /  _____  \ | |  | || |____| |__| |  \  /   | |____ | | \ \  )");
    mvwprintw(win, getmaxy(win)/2-1, (getmaxx(win)/2)-(textLen/2), R"(  \_____|/__/     \__\|_|  |_||______|\____/    \/    |______||_|  \_\ )");

    
        echo();
        mvwprintw(win, max_y*0.6, (getmaxx(win)/2-17), "insert your name to save score : ");
        char str[4];
        flushinp();    
        wgetstr(win,str); 
        strncpy(dp.name, str, 4);
        dp.score = score;
        noecho();

        // gameOver(win);
        // mvwprintw(win, max_y*0.6-2, max_x/2, "max 3 charachters");

    return dp;
}
