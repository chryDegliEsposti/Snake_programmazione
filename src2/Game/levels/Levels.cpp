#include "Levels.hpp"

level* createNode(int id, int speed, int snakeLen, int bonus) {
    level* node = new level;
    node->id       = id;
    node->speed    = speed;
    node->snakeLen = snakeLen;
    node->bonus    = bonus;
    node->next     = nullptr;
    return node;
}

void insertAtHead(level*& head, int id, int speed, int snakeLen, int bonus) {
    level* node = createNode(id, speed, snakeLen, bonus);
    node->next = head;
    head = node;
}

void insertAtTail(level*& head, int id, int speed, int snakeLen, int bonus) {
    level* node = createNode(id, speed, snakeLen, bonus);
    if (!head) {
        head = node;
        return;
    }
    level* cur = head;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = node;
}

level* findNode(level* head, int id) {
    for (level* cur = head; cur; cur = cur->next) {
        if (cur->id == id)
            return cur;
    }
    return nullptr;
}

bool deleteNode(level*& head, int id) {
    if (!head) return false;
    if (head->id == id) {
        level* toDelete = head;
        head = head->next;
        delete toDelete;
        return true;
    }
    level* cur = head;
    while (cur->next && cur->next->id != id) {
        cur = cur->next;
    }
    if (!cur->next) {
        return false;
    }
    level* toDelete = cur->next;
    cur->next = toDelete->next;
    delete toDelete;
    return true;
}

void printList(const level* head) {
    const level* cur = head;
    while (cur) {
        std::cout << "[id="       << cur->id
                  << ", speed="   << cur->speed
                  << ", len="     << cur->snakeLen
                  << ", bonus="   << cur->bonus
                  << "] -> ";
        cur = cur->next;
    }
    std::cout << "NULL\n";
}

void clearList(level*& head) {
    while (head) {
        level* next = head->next;
        delete head;
        head = next;
    }
}
