#ifndef LEVELS_HPP
#define LEVELS_HPP

#include <cstddef>

class levels {
public:
    struct level {
        level* next;
        level* before;
        int    num;
        int    vel;
        float  bonus;
        int    snakelen;
    };

    // crea la lista con [numLastLevel] livelli
    explicit levels(int numLastLevel);
    ~levels();

    // non copiabile (per evitare doppi delete); movibile opzionalmente
    levels(const levels&)            = delete;
    levels& operator=(const levels&) = delete;

    // navigazione
    level* nextLevel();
    level* beforeLevel();
    level* getCurrLevel();
    level* getHead();
    level* goToLevel(int num);

    // utilità
    int    size() const { return count; }

private:
    void addLevel(int num, int vel, float bonus, int snakelen);
    void addAllLevels(int numLastLevel);

    level* head   = nullptr;
    level* tail   = nullptr;
    level* curr   = nullptr;
    int    count  = 0;
};

#endif