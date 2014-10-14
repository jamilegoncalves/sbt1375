#include "Permutation.h"
#include "PermutationArray.h"
#include "BreakpointGraph.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <list>
#include <limits>
#include <sys/time.h>

BreakpointGraph::BreakpointGraph(Permutation *p)
{
    this->p = p;
    int n = p->getNumElmts();

    Permutation *inverse = p->getInverse();

    adjacencies = new BPGAdjacency[2*n+2];

    adjacencies[0].vertex = 0;
    adjacencies[0].reality = 1;
    adjacencies[0].desire = 2 * inverse->getElement(1)-1;

    for (int i = 1; i <= n; i++)
    {
        adjacencies[2*i-1].vertex = -(p->getElement(i));
        adjacencies[2*i].vertex = p->getElement(i);

        adjacencies[2*i-1].reality = 2*i-2;
        adjacencies[2*i].reality = 2*i+1;

        adjacencies[2*i].desire = 2 *
            inverse->getElement(adjacencies[2*i].vertex + 1) - 1;
        adjacencies[2*i-1].desire = 2 *
            inverse->getElement(adjacencies[2*i].vertex - 1);
    }

    adjacencies[2*n+1].vertex = -(n+1);
    adjacencies[2*n+1].reality = 2*n;
    adjacencies[2*n+1].desire = 2 *
        inverse->getElement(n);

    delete inverse;
}

BreakpointGraph::~BreakpointGraph()
{
    delete adjacencies;
}

/**
 * Método que classifica os ciclos do grafo:
 * oneCycles, twoCycles, threeCycles and longCycles
 */
void BreakpointGraph::Cycles()
{
    int n = p->getNumElmts();
    bool *mark = new bool[2*n+2];
    int length = 0;
    int i=0;

    for(i = 0; i < 2*n+2; i++)
    {
        mark[i] = false;
    }

    for(i = 0; i < 2*n+1; i++)
    {
        while(mark[i] == false)
        {
            mark[i] = true;
            mark[adjacencies[i].desire] = true;
            
            if(mark[adjacencies[adjacencies[i].desire].reality] == false)
            {
                i = adjacencies[adjacencies[i].desire].reality;
                ++length;
            }
/* TODO: descomentar
 *             else if(length == 1)
                oneCycles.push_back(adjacencies[i]);
            else if(length == 2)
                twoCycles.push_back(adjacencies[i]);
            else if(length == 3)
                threeCycles.push_back(adjacencies[i]);
            else
                longCycles.push_back(adjacencies[i]);*/
        }
    }
    delete mark;
}

/**
 * Método que transforma o grafo em um grafo simples:
 * somente ciclos com comprimento menor que 4
 */

void BreakpointGraph::simpleBreakpointGraph()
{
    int length = 0;
    
    while(!longCycles.empty())
    {
        //int i = longCycles.front();
        //longCycles.pop_front();

    }
}

/**
 * Método que retorna o número de ciclos ímpares no grafo
 */

int BreakpointGraph::oddCycles()
{
    int n = p->getNumElmts();
    bool *mark = new bool[2*n+2];

    int numCycles = 0;
    int numVertex = 0;
    int i=0;

    for(i = 0; i < 2*n+2; i++)
    {
        mark[i] = false;
    }

    for(i = 0; i < 2*n+1; i++)
    {
        while(mark[i] == false)
        {
            mark[i] = true;
            mark[adjacencies[i].desire] = true;

            numVertex = numVertex+2;

            if(mark[adjacencies[adjacencies[i].desire].reality] == false)
            {
                i =  adjacencies[adjacencies[i].desire].reality;
            }
            else if(numVertex%4 != 0)
            {
                numCycles = numCycles++;
                numVertex = 0;
                i=0;
            }
            else
            {
                numVertex = 0;
                i=0;
            }
        }
    }
    delete mark;
    return numCycles;
}

/**
 * Método que calcula o limite inferior da distância de transposição
 */

int BreakpointGraph::transpositionDistanceLowerBound()
{
    int d = ceil( (double)( p->getNumElmts() + 1 - oddCycles() ) / 2 );

    return d;
}

/**
 * Método que calcula o limite superior da distância de transposição
 */

int BreakpointGraph::transpositionDistanceUpperBound()
{
    int d = ceil( 3.0/4.0 * (double)(p->getNumElmts() + 1 - oddCycles()) );

    return d;
}

std::ostream &operator<<(std::ostream &os, BreakpointGraph *g)
{
    int n = g->p->getNumElmts();

    for(int i = 0; i < 2*n+2; i++)
    {
        os << g->adjacencies[i].vertex << "\t"
                << g->adjacencies[i].reality << "\t"
                << g->adjacencies[i].desire << std::endl;
    }
    return os;
}
