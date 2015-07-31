#include "AdjacencyList.h"
#include <algorithm>
#include <cstring>
#include <assert.h>

using namespace std;
using namespace BPG;

int getIndex(int vertex)
{
    return (vertex >= 0) ? 2*vertex : 2*abs(vertex)-1;
}

bool Adjacency::isValid()
{
    return (vertex != 0) || (reality != 0) || (desire != 0);
}

AdjacencyListIterator::AdjacencyListIterator(AdjacencyList *thelist)
: n(thelist->n), current(-1), nextUnvisitedVertex(-1), list(thelist)
{
    reallocVisitedArray();
}

AdjacencyListIterator::~AdjacencyListIterator()
{
}

bool AdjacencyListIterator::visit()
{
    assertCurrentIsValid();
    if (!visited[current])
    {
        if (current == 0 && nextUnvisitedVertex == -1) {
            nextUnvisitedVertex = 1;
        }
        visited[current] = true;
        return true;
    }
    else
    {
        return false;
    }
}

bool AdjacencyListIterator::nextReality()
{
    assertCurrentIsValid();
    current = (*list)[current].reality;
    return visit();
}

bool AdjacencyListIterator::nextDesire()
{
    assertCurrentIsValid();
    current = (*list)[current].desire;
    return visit();
}

bool AdjacencyListIterator::nextUnvisited()
{
    if (nextUnvisitedVertex > n)
    {
        return false;
    }
    if (nextUnvisitedVertex == -1) {
        nextUnvisitedVertex = 0;
        current = 0;
        return visit();
    }
    ++nextUnvisitedVertex;
    while (nextUnvisitedVertex <= n)
    {
        if ( (*list)[nextUnvisitedVertex].isValid()
                && !visited[nextUnvisitedVertex])
        {
            current = nextUnvisitedVertex;
            return visit();
        }
        ++nextUnvisitedVertex;
    }
    return false;
}

bool AdjacencyListIterator::setTo(int vertex)
{
    if ( !visited[vertex] )
    {
        current = vertex;
        visit();
        return true;
    }
    else
    {
        return false;
    }
}

Adjacency &AdjacencyListIterator::get()
{
    return (*list)[current];
}

void AdjacencyListIterator::reallocVisitedArray()
{
    n = list->n;
    visited.setN(list->n);
}

void AdjacencyListIterator::assertCurrentIsValid()
throw(AdjacencyListIndexError)
{
    if (current < -(n+1) || current > n)
    {
        AdjacencyListIndexError e(
                "Incorrect call to AdjacencyListIterator::visit()");
        throw e;
    }
}

AdjacencyList::AdjacencyList() : adj(NULL), n(0)
{
}

AdjacencyList::~AdjacencyList()
{
  if (adj != NULL)
    delete adj;
}

void AdjacencyList::setN(int n) {
    assert(adj == NULL);
    adj = new Adjacency[2*n+2]();
    this->n = n;
}

void AdjacencyList::print(ostream& os) {
    os << "vertex" << "\t" << 0;
    for (int i=1; i<= n; ++i) {
        os << "\t" << -i << "\t" << i;
    }
    os << "\t" << -(n+1) << std::endl;

    os << "reality" << "\t" << this->operator[](0).reality;
    for (int i=1; i<= n; ++i) {
        os << "\t" << this->operator[](-i).reality << "\t"
                << this->operator[](i).reality;
    }
    os << "\t" << -this->operator[](-(n+1)).reality << std::endl;

    os << "desire" << "\t" << this->operator[](0).desire;
    for (int i=1; i<= n; ++i) {
        os << "\t" << this->operator[](-i).desire << "\t" 
                << this->operator[](i).desire;
    }
    os << "\t" << -this->operator[](-(n+1)).desire << std::endl;
}

Adjacency &AdjacencyList::operator[](int vertex)
{
    assert(vertex >= -(n+1));
    assert(vertex <= n);
    // positive vertices are mapped to even indexes
    // negative vertices are mapped to odd indexes
    return adj[getIndex(vertex)];
}

VisitedList::VisitedList() : visited(NULL), n(0)
{
}

VisitedList::~VisitedList()
{
  if (visited != NULL)
    delete visited;
}

void VisitedList::setN(int n)
{
    assert(n > 0);
    if (visited == NULL) {
        visited = new bool[2*n+2]();
    } else {
        int newsize = 2*n+2;
        bool *newv = new bool[newsize]();
        int numCopy = min(2*(this->n)+2, newsize);
        memcpy(newv, visited, numCopy*sizeof(bool));
        delete visited;
        visited = newv;
    }
    this->n = n;
}

bool &VisitedList::operator[](int vertex)
{
    int idx = getIndex(vertex);
    assert(idx >= 0);
    assert(idx < 2*n+2);
    // positive vertices are mapped to even indexes
    // negative vertices are mapped to odd indexes
    return visited[idx];
}

AdjacencyListIndexError::AdjacencyListIndexError() throw() : msg("")
{
}

AdjacencyListIndexError::AdjacencyListIndexError(const char *msg)
throw() : msg(msg)
{
}

AdjacencyListIndexError::~AdjacencyListIndexError()
throw()
{
}

const char *AdjacencyListIndexError::what()
const throw()
{
    return msg.c_str();
}
