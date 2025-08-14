#include "Game.hpp"


int Game::getMillis() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return uint64_t(ts.tv_sec) * 1000 + ts.tv_nsec / 1000000;
}

Game::Game(): snake(3, 20, 20){
    this->max_x = getmaxx(stdscr);
    this->max_y = getmaxy(stdscr);
    this->width = max_x*0.8;
    this->height = max_y*0.8;
    this->score = 0;
}

char Game::getInput(WINDOW*win) {
    int TIMEOUT = 500;
    int start = getMillis();
    char lastInput = ERR;
    timeout(0);
    int i = 0;
    while((getMillis() - start) <= TIMEOUT) {
        //mvwprintw(win, 0, 20, "%d", (getMillis() - start));
        char temp = getch();
        if(temp != ERR)
            lastInput = temp;
    }
    return lastInput;
}

WINDOW* Game::setBoard(){
    WINDOW*win = newwin(height, width, max_y*0.1, max_x*0.1);
    refresh();

    box(win, 0,0);
    wrefresh(win);
    return win;
}

void Game::run(WINDOW*win,int start){    
    
    attroff(COLOR_PAIR(2));
    char last_chinput = 'd';
    while(1) {
        char chinput = getInput(win);
        
        if(chinput == ERR) {
            chinput = last_chinput;
        }
        if(!snake.snake_move(chinput, &snake.y, &snake.x)) {
            snake.snake_move(last_chinput, &snake.y, &snake.x);
        } else last_chinput = chinput;
        
        mvwprintw(win, snake.cibo->y, snake.cibo->x, "%c", snake.cibo->type);
        wrefresh(win);

        if(!GameLoop(win, start)) break;
        wrefresh(win);


        if(snake.x >= width-1 || snake.y >= height-1 || snake.x <= 0 || snake.y <= 0) {
            snake.x = snake.head->x;
            snake.y = snake.head->y;
            break;
        }

        bool tailBitten = false;
        
        Object* temp = snake.tail;

        do {
            if(temp->x == snake.x && temp->y == snake.y) {
                snake.x = snake.head->x;
                snake.y = snake.head->y;
                tailBitten = true;
                break;
            }
        } while((temp = temp->next) != nullptr);
        if(tailBitten) {
            break;
        }

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
    }


}

bool Game::GameLoop(WINDOW* win, int gameStartMillis){
    uint64_t elapsed = getMillis() - gameStartMillis;
    int remaining = MAX_TIME - elapsed;
    if(remaining < 0) remaining = 0;

    int mm = (remaining / 1000) / 60;
    int ss = (remaining / 1000) % 60;
    mvwprintw(stdscr, max_y*0.05, (max_x*0.1)+1,
              "TIME : %02d:%02d", mm, ss);
    mvwprintw(stdscr, max_y*0.05, (max_x*0.5),
              "SCORE : %d", score);
    mvwprintw(stdscr, max_y*0.9, (max_x*0.5)-2,
              "LEVEL : %d", 1);
    wrefresh(stdscr);

    if (getMillis() - gameStartMillis >= MAX_TIME) {// tempo scaduto
        return false;
    }
    return true;
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
