#include "levels.hpp"

void levels::addLevel(int num, int vel, float bonus, int snakelen) {
    level* newLevel = new level{nullptr, nullptr, num, vel, bonus, snakelen};

    if (!head) {
        head = tail = curr = newLevel;
    } else {
        tail->next = newLevel;
        newLevel->before = tail;
        tail = newLevel;
    }
    count++;
}

void levels::addAllLevels(int numLastLevel) {
    int currNum = 1;
    float vel = 10;
    float bonus = 1.2f;
    float snakelen = 3;

    while (currNum <= numLastLevel) {
        addLevel(currNum, (int)vel, bonus, (int)snakelen);
        currNum++;
        vel += 3;
        bonus += 0.2f;
        snakelen +=0.75;
    }
}

levels::levels(int numLastLevel) {
    addAllLevels(numLastLevel);
}

levels::~levels() {
    level* it = head;
    while (it) {    // per ogni elemento nella lista, rimuoviamo dall'heap
        level* nxt = it->next;
        delete it;
        it = nxt;
    }
    head = tail = curr = nullptr;
    count = 0;
}

levels::level* levels::nextLevel() {
    if (curr && curr->next) curr = curr->next;
    return curr;
}

levels::level* levels::beforeLevel() {
    if (curr && curr->before) curr = curr->before;
    return curr;
}

levels::level* levels::getCurrLevel() { return curr; }
levels::level* levels::getHead()      { return head; }

levels::level* levels::goToLevel(int num) {
    level* tmp = head;
    while (tmp) {
        if (tmp->num == num) {
            curr = tmp;
            return curr;
        }
        tmp = tmp->next;
    }
    return nullptr;
}
