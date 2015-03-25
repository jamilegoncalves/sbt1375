#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H
#include <exception>
#include <string>
#include <iostream>

namespace BPG
{

    typedef struct
    {
        int vertex;
        int reality;
        int desire;
        bool isValid();
    } Adjacency;
    
    class AdjacencyList
    {
        friend class AdjacencyListIterator;
    private:
        Adjacency *adj;
        int n;

    public:
        AdjacencyList();
        ~AdjacencyList();
        void setN(int n);
        Adjacency &operator[](int vertex);
    };

    class AdjacencyListIndexError : public std::exception
    {
    public:
        AdjacencyListIndexError() throw();
        AdjacencyListIndexError(const char *msg) throw();
        ~AdjacencyListIndexError() throw();
        const char* what() const throw();
    private:
        std::string msg;
    };

    class VisitedList
    {
    private:
        bool *visited;
        int n;
        int size;

    public:
        VisitedList();
        ~VisitedList();
        void setN(int n);
        bool &operator[](int vertex);
    };

    class AdjacencyListIterator
    {
    public:
        AdjacencyListIterator(AdjacencyList *thelist);
        ~AdjacencyListIterator();
        /**
         * Moves the iterator to the next unvisited vertex in a cycle
         * via a reality edge, and visits the vertex.
         * @return true if possible, false if all vertices have been visited
         */
        bool nextReality();
        /**
         * Moves the iterator to the next unvisited vertex in a cycle
         * via a desire edge, and visits the vertex.
         * @return true if possible, false if all vertices have been visited
         */
        bool nextDesire();
        /**
         * Moves the iterator to the next unvisited vertex and visits it.
         * This function should only be called after visiting all vertices
         * in a cycle.
         * @return true if possible, false if all vertices have been visited
         */
        bool nextUnvisited();

        /**
         * Moves the iterator to a specific vertex and visits it.
         * @param vertex, the label of the vertex, in the range -(n+1)..n
         * @return true if the vertex was not visited before, false otherwise
         */
        bool setTo(int vertex);

        /**
         * Gets the adjacency object to which this iterator is pointing.
         */
        Adjacency &get();

    private:
        bool visit();
        void reallocVisitedArray();
        void assertCurrentIsValid() throw(AdjacencyListIndexError);

        VisitedList visited;
        size_t visitedlen;
        int n;
        int current;
        int nextUnvisitedVertex;
        AdjacencyList *list;
    };

}

#endif
