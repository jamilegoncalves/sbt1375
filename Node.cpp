#include "Node.h"
#include <string.h>

NodeArray::NodeArray(int capacity)
{
    nodes = new Node*[capacity]();
    this->capacity = capacity;
    size = 0;
}

NodeArray::~NodeArray()
{
    delete nodes;
}

Node* NodeArray::get(int i)
{
    if(i < size)
        return nodes[i];
    else
        return NULL;
}

void NodeArray::put(Node *n, int i)
{
    if(i >= capacity)
    {
        capacity = 2*i;
        Node **newnodes = new Node*[capacity]();
        memcpy(newnodes, nodes, size*sizeof(Node*));
        delete nodes;
        nodes = newnodes;
    }
    nodes[i] = n;
    if(size < i+1)
        size = i+1;
}

void NodeArray::clear()
{
    for(int i = 0; i < size; ++i)
        nodes[i] = NULL;
    size = 0;
}

void NodeArray::print(std::ostream &os) {
    for(int i = 1; i < size; ++i) {
        if (nodes[i] != NULL)
            os << nodes[i]->gene << " ";
        else
            os << "x" << " ";
    }
    os << std::endl;
}

