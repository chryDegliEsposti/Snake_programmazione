#include "graphicFuncs.hpp"
#include <ncurses.h>
#include "../Levels/levels.hpp"

class levelGraphics{

    private: 
        int maxx,maxy;
        levels *l;


    public:
        levelGraphics();
        void printLevel(levels::level *currLev);
        void printAllLevel();
        void level();

};