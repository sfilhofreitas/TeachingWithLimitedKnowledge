#ifndef UTIL_LIST_H
#define UTIL_LIST_H
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
typedef struct Node{
    public:
    int data;
    Node* next;
    Node* prev;
}Node;

class UtilList{
    Node* head;
    Node* tail;
    int size;
public:
    UtilList();
    ~UtilList();
    void push_back(int data);
    void push_back(Node* node, int data);
    void erase(Node *node);
    void eraseAll();
    void print_list();
    int getSize() const;
    int getHeadValue() const;
};

#endif // UTIL_LIST_H
