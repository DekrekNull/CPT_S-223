#include <iostream>
#include <cstdlib>
#include <ctime>
#ifndef SLLIST_H
#define SLLIST_H

template <class T> class Node {
public:
    T command;
    T description;

    Node<T>* next;
    Node(T cmd, T desc);
};

template <class T> class SLList {
private:
    Node<T>* head;
    bool contains(T cmd) ;
    int n;

public:
    SLList(T cmd, T desc);
    SLList<T>* clone();

    bool insertAtFront(T cmd, T desc);
    bool removeNode(T cmd);
    T getRandomDescription(T cmd);
    Node<T>* getAndRemoveRandomCommand();
    int getLength();
    void addNode(T cmd, T desc);

    ~SLList();

};

#endif //SLLIST_H
