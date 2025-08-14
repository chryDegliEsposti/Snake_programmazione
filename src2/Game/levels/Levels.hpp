#ifndef LEVELS_HPP
#define LEVELS_HPP

#include <iostream>

struct level {
    int id;
    int speed;
    int snakeLen;
    int bonus;
    level *next;
};

level* createNode(int id, int speed, int snakeLen, int bonus);
void insertAtHead(level*& head, int id, int speed, int snakeLen, int bonus);
void insertAtTail(level*& head, int id, int speed, int snakeLen, int bonus);
level* findNode(level* head, int id);
bool deleteNode(level*& head, int id);
void printList(const level* head);
void clearList(level*& head);

#endif