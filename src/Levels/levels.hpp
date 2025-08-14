#ifndef LEVELS_HPP
#define LEVELS_HPP

#include <cstddef>
#include <vector>

class levels {

    public: 

    struct level {
        level* next;
        level* before;
        int num;
        int vel;
        float bonus;
        int snakelen;
    };

    levels(int numLastLevel);
    void addLevel(int num, int vel, float bonus, int snakelen);
    void addAllLevels(int numLastLevel);
    level* nextLevel();
    level* beforeLevel();
    level* getCurrLevel();
    level* goToLevel(int num);
    void printLevelList(const level* head);

    private:
    level* head;
    level* curr;

};

#endif