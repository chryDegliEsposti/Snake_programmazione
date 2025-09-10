#ifndef LEVELS_HPP
#define LEVELS_HPP

#include <cstddef>

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

    // crea la lista dei livelli fino a numLastLevel
    levels(int numLastLevel);
    ~levels();

    levels(const levels&)= delete;

    // navigazione
    level* nextLevel();
    level* beforeLevel();
    level* getCurrLevel();
    level* getHead();
    level* goToLevel(int num);

    int size() const {
        return count;
    }

private:
    void addLevel(int num, int vel, float bonus, int snakelen);
    void addAllLevels(int numLastLevel);

    level* head = nullptr;
    level* tail = nullptr;
    level* curr = nullptr;
    int count  = 0;
};

#endif