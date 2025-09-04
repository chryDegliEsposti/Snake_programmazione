#include <ncurses.h>
#include "../Levels/levels.hpp"

class levelGraphics {
public:
    levelGraphics(levels& lvls);
    ~levelGraphics() = default;

    levels* getLevelsList();

    levels::level* selectLevel();


private:
    levels* l;
    int maxy = 0;
    int maxx = 0;
};
