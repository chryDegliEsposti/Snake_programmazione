#include "levels.hpp"

void levels::addLevel(int num, int vel, float bonus, int snakelen) {
    levels::level* newLevel = new levels::level{nullptr, nullptr, num, vel, bonus, snakelen};
    
    if(!head) {
        head = newLevel;
        curr = head;
    }else {
        levels::level* tmp = head;
        while(tmp->next) {
            tmp = tmp->next;
        }   
        tmp->next = newLevel;
        newLevel->before = tmp;     
    }
}

void levels::addAllLevels(int numLastLevel) {
    int currNum = 1;
    int vel = 10;                       //da scegliere per bene dopo
    float bonus = 1.2;
    int snakelen = 5;

    while(currNum <= numLastLevel) {
        addLevel(currNum, vel, bonus, snakelen);
        currNum++;
        vel += 5;
        bonus += 0.2;
        snakelen++;
    }
}

levels::levels(int numLastLevel) {
    addAllLevels(numLastLevel);
}

levels::level* levels::nextLevel() {
    if(curr && curr->next) {
        curr = curr->next;
    }

    return curr;
}

levels::level* levels::beforeLevel() {
    if(curr && curr->before) {
        curr = curr->before;
    }

    return curr;
}

levels::level* levels::getCurrLevel() {
    return curr;
}

levels::level* levels::goToLevel(int num) {
    levels::level* tmp = head;

    while(num != tmp->num && tmp->next){
        tmp = tmp->next;

        if(tmp && tmp->num == num) {
            curr = tmp;
            return curr;
        }
    }

    return nullptr;
}
