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
#include <assert.h>

using namespace BPG;

BreakpointGraph::BreakpointGraph(Permutation *p)
{    
    debug = p;
    n = p->getNumElmts();
    adjlist = new AdjacencyList();
    AdjacencyList &adjacencies = *adjlist;
    adjacencies.setN(2*n+1); // allocates enough space for renumbering

    adjacencies[0].vertex = 0;
    adjacencies[0].reality = -p->getElement(1);
    adjacencies[0].desire = -1;

    for (int i = 1; i <= n; i++)
    {
        int pi_i = p->getElement(i);
        int pi_iplus1 = p->getElement(i+1);
        int pi_iminus1 = p->getElement(i-1);

        adjacencies[+pi_i].vertex = +pi_i;
        adjacencies[+pi_i].reality = -pi_iplus1;
        adjacencies[+pi_i].desire = -(pi_i + 1);

        adjacencies[-pi_i].vertex = -pi_i;
        adjacencies[-pi_i].reality = +pi_iminus1;
        adjacencies[-pi_i].desire = +(pi_i - 1);
    }

    adjacencies[-(n+1)].vertex = -(n+1);
    adjacencies[-(n+1)].reality = p->getElement(n);
    adjacencies[-(n+1)].desire = n;
    
   /*
    for(int i = 0; i < 2*n+2; i++)
    {
        std::cout<< "Vértice: " << adjacencies[i].vertex <<std::endl;
        std::cout<< "Realidade: " << adjacencies[i].reality <<std::endl;
        std::cout<< "Desejo: " << adjacencies[i].desire <<std::endl;
        std::cout<<"\n";
    }
*/
}

BreakpointGraph::~BreakpointGraph()
{
    delete adjlist;
}

Permutation* BreakpointGraph::simplePermutation()
{
    cycles();
    simpleBreakpointGraph();
    renumber();
    return toPermutation();
}
//BPG::Adjacency &BreakpointGraph::followRealityEdge(BPG::Adjacency &adj)
BPG::Adjacency &BreakpointGraph::followRealityEdge(BPG::Adjacency &adj)
{
    return (*adjlist)[adj.reality];
}

BPG::Adjacency &BreakpointGraph::followDesireEdge(BPG::Adjacency &adj)
{
    return (*adjlist)[adj.desire];
}

/**
 * Método que classifica os ciclos do grafo:
 * oneCycles, twoCycles, threeCycles and longCycles
 */
void BreakpointGraph::cycles()
{
    AdjacencyListIterator it(adjlist);

    while (it.nextUnvisited()) {
        Adjacency& firstAdj = it.get();
        int length = 0;
        while (it.nextReality()) {
            it.nextDesire();
            ++length;
        }
        switch (length)
        {
            case 0:
                throw (const char *)"Should never happen!";
            case 1:
                oneCycles.push_back(&firstAdj);
                break;
            case 2:
                twoCycles.push_back(&firstAdj);
                break;
            case 3:
                threeCycles.push_back(&firstAdj);
                break;
            default:
                longCycles.push_back(&firstAdj);
                break;
        } 
    }
}

/**
 * Método que transforma o grafo em um grafo simples:
 * somente ciclos com comprimento 1, 2 ou 3. 
 */
void BreakpointGraph::simpleBreakpointGraph()
{
    if (longCycles.empty())
        return;
 
    int length;
    int first;
    Adjacency *firstAdj;
    Adjacency *lastAdj;
    AdjacencyListIterator it(adjlist);
    AdjacencyList &adjacencies = *adjlist;
    while(!longCycles.empty())
    {
        length = 0;
        firstAdj = longCycles.front();
        first = firstAdj->vertex;
        it.setTo(firstAdj->vertex);
        longCycles.pop_front();

        it.nextReality();
        
        while(it.nextDesire())
        {
            lastAdj = &it.get();
            ++length;
            it.nextReality();

            //if( (it.get().vertex != firstAdj->vertex) && (length >= 2) )            
            if( (it.get().desire != first) && (length >= 2) )
            {
                // Novas adjacencias:
                adjacencies[-(n+2)].vertex = -(n+2);
                adjacencies[-(n+2)].reality = lastAdj->vertex;
                adjacencies[-(n+2)].desire = firstAdj->vertex;
                
                adjacencies[n+2].vertex = n+2;
                adjacencies[n+2].reality = it.get().vertex;
                
                // Alterações:
                adjacencies[firstAdj->vertex].desire = -(n+2);
                adjacencies[lastAdj->vertex].reality = -(n+2);
                adjacencies[it.get().vertex].reality = n+2;
                
                firstAdj = &adjacencies[n+2];
                length = 0;
                ++n;
            }
        }

        adjacencies[lastAdj->reality].desire = firstAdj->vertex;        
        adjacencies[firstAdj->vertex].desire = lastAdj->reality;        
    }
}

#define remap(x) (x < 0) ? -oldToNew[-x] : oldToNew[x]

void BreakpointGraph::renumber()
{
    int *oldToNew = new int[n+2];
    oldToNew[0] = 0;
    int renumbered = 1;
    AdjacencyListIterator it(adjlist);    
    int current = 0;
    
    while(renumbered <= n+1)
    {
        it.setTo(-current);
        it.nextDesire();
        current = it.get().vertex;
        oldToNew[-current] = renumbered;
        ++renumbered;
    }

    AdjacencyList *newAdjlist = new AdjacencyList();
    newAdjlist->setN(n);
    AdjacencyList &newAdjacencies = *newAdjlist;
    AdjacencyListIterator it2(adjlist);
    int newvertex;

    for(int i = 0; i <= n+1; ++i)
    {
        it2.setTo(i);
        Adjacency &old = it2.get();
        if( (old.reality != 0) && (old.desire != 0) )
        {
            newvertex = remap(old.vertex);
            newAdjacencies[newvertex].vertex = newvertex;
            newAdjacencies[newvertex].reality = remap(old.reality);
            newAdjacencies[newvertex].desire = remap(old.desire);            
        }
        
        it2.setTo(-i);
        old = it2.get();
        newvertex = remap(old.vertex);
        newAdjacencies[newvertex].vertex = newvertex;
        newAdjacencies[newvertex].reality = remap(old.reality);
        newAdjacencies[newvertex].desire = remap(old.desire);
    }
    
    delete adjlist;
    adjlist = newAdjlist;
    delete oldToNew;
}

Permutation *BreakpointGraph::toPermutation()
{
    AdjacencyListIterator it(adjlist);
    
    int* newElmts = new int[n];
    int current;
    int i = 0;
    it.setTo(0);
    
    while(i < n)
    {
        it.nextReality();
        current = it.get().vertex;
        it.setTo(-current);
        newElmts[i] = it.get().vertex;
        ++i;
    }
    
    Permutation *pA = new PermutationArray(newElmts, n);
    
    delete newElmts;
    return pA;
}

/**
 * Método que retorna o número de ciclos ímpares no grafo
 */

int BreakpointGraph::oddCycles()
{
    AdjacencyList &adjacencies = *adjlist;
    bool mark[4*n+1];

    int numCycles = 0;
    int numVertex = 0;
    int i=0;

    for(i = 0; i < 4*n+2; i++)
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
                ++numCycles;
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
    return numCycles;
}

/**
 * Método que calcula o limite inferior da distância de transposição
 */

int BreakpointGraph::transpositionDistanceLowerBound()
{
    int d = ceil( (double)( n + 1 - oddCycles() ) / 2 );

    return d;
}

/**
 * Método que calcula o limite superior da distância de transposição
 */

int BreakpointGraph::transpositionDistanceUpperBound()
{
    int d = ceil( 3.0/4.0 * (double)(n + 1 - oddCycles()) );

    return d;
}

std::ostream &operator<<(std::ostream &os, BreakpointGraph *g)
{
    AdjacencyList &adjacencies = *(g->adjlist);
    int n = g->n;

    for(int i = 0; i < 2*n+2; i++)
    {
        os << adjacencies[i].vertex << "\t"
                << adjacencies[i].reality << "\t"
                << adjacencies[i].desire << std::endl;
    }
    return os;
}
