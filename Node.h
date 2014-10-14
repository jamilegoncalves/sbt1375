#ifndef NODEARRAY_H
#define	NODEARRAY_H
#include <iostream>

typedef struct Node {
    int gene;
    struct Node *left;
    struct Node *right;
    int height;
    int leavesInSubtree;
} Node;

class NodeArray{
public:
    NodeArray(int capacity);
    ~NodeArray();
    Node *get(int i);
    void put(Node *n, int i);
    void clear();
    void print(std::ostream &os);
private:
    Node **nodes;
    int size;
    int capacity;
};

#endif	/* NODEARRAY_H */


