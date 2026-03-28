#ifndef NODE_H
#define NODE_H
#include <iomanip>
#include <iostream>
using namespace std;

template <typename T>
struct node{
    T _item;
    node<T>* _next;
    node<T>* _prev;

    node(const T& item = T(), node<T>* next = nullptr, node<T>* prev = nullptr) 
        : _item(item) , _next(next), _prev(prev) {}

    friend ostream& operator<<(ostream& outs, const node<T>& printMe){
        outs << "" << printMe._item << "";
        return outs;
    }
};

#endif