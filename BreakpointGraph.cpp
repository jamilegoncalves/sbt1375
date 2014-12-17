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
    n = p->getNumElmts();

    Permutation *inverse = p->getInverse();

    adjacencies = new BPGAdjacency[4*n+1];

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
    delete adjacencies;
}

/**
 * Método que classifica os ciclos do grafo:
 * oneCycles, twoCycles, threeCycles and longCycles
 */
void BreakpointGraph::cycles()
{
    bool mark[2*n+1];
    int length = 0;
    int i=0;

    for(i = 0; i < 2*n+2; i++)
    {
        mark[i] = false;
    }

    for(i = 0; i < 2*n+2; i++)
    {
        while(mark[i] == false)
        {
            mark[i] = true;
            mark[adjacencies[i].desire] = true;
            ++length;
            
            if(mark[adjacencies[adjacencies[i].desire].reality] == false)
            {
                i = adjacencies[adjacencies[i].desire].reality;
            }
            else if(length == 1)
            {
                oneCycles.push_back(i);
                length = 0;
                i=0;
            }
            else if(length == 2)
            {
                twoCycles.push_back(i);
                length = 0;
                i=0;
            }
            else if(length == 3)
            {
                threeCycles.push_back(i);
                length = 0;
                i=0;
            }
            else
            {
                longCycles.push_back(i);
                length = 0;
                i=0;
            }
        }
    }
    
    /*
    std::cout<<"OneCycles: " << oneCycles.size() <<std::endl;
    std::cout<<"TwoCycles: " << twoCycles.size() <<std::endl;
    std::cout<<"ThreeCycles: " << threeCycles.size() <<std::endl;
    std::cout<<"LongCycles: " << longCycles.size() <<std::endl;
    */
}

Permutation* BreakpointGraph::simplePermutation()
{
    cycles();
    simpleBreakpointGraph();
    renumberBreakpointGraph();
    return toPermutation();
}

/**
 * Método que transforma o grafo em um grafo simples:
 * somente ciclos com comprimento menor que 4
 */
void BreakpointGraph::simpleBreakpointGraph()
{
    bool mark[4*n+1];
    int sizeTable = 2*n+1;
    int length = 0;
    int i=0;
    int first;

    for(i = 0; i < 4*n+2; i++)
    {
        mark[i] = false;
    }
    
    while(!longCycles.empty())
    {
        i = longCycles.front();
        longCycles.pop_front();
        first = i;

        while(mark[i] == false)
        {
            mark[i] = true;
            mark[adjacencies[i].reality] = true;
            ++length;
            
            if( length < 3 )
            {
                i = adjacencies[adjacencies[i].reality].desire;
            }    
            else if(adjacencies[adjacencies[i].reality].desire != first)
            {
                // Novas adjacencias:
                adjacencies[sizeTable+1].vertex = -(n+2);
                adjacencies[sizeTable+1].reality = i;
                adjacencies[sizeTable+1].desire = first;

                adjacencies[sizeTable+2].vertex = n+2;
                adjacencies[sizeTable+2].reality = adjacencies[i].reality;
                adjacencies[sizeTable+2].desire = adjacencies[first].desire;
                
                // Atualização das demais adjacencias:
                adjacencies[adjacencies[first].desire].desire = sizeTable+2;
                adjacencies[first].desire = sizeTable+1;
                adjacencies[adjacencies[i].reality].reality = sizeTable+2;
                adjacencies[i].reality = sizeTable+1;
                
                mark[sizeTable+1] = true;
                i = sizeTable+2;
                length = 0;
                first = i;

                sizeTable = sizeTable+2;
                ++n;                
            }
        }
    }
/*
    for(int i = 0; i < 26; i++)
    {
        std::cout<< "Vértice: " << adjacencies[i].vertex <<std::endl;
        std::cout<< "Realidade: " << adjacencies[i].reality <<std::endl;
        std::cout<< "Desejo: " << adjacencies[i].desire <<std::endl;
        std::cout<<"\n";
    }
*/
}

void BreakpointGraph::renumberBreakpointGraph()
{
    int posInAdjacencies[2*n+2];
    int idxzero = n+1;
    int j = 0;
    int newNumber = 1;
    int temp;
    
    for(int i = 0; i < 2*n+2; ++i)
    {
        posInAdjacencies[idxzero+adjacencies[i].vertex] = i;
    }
    
    // Renumeração:
    do
    {
        temp = adjacencies[adjacencies[j].desire].vertex;
        adjacencies[adjacencies[j].desire].vertex = -newNumber;
        j = posInAdjacencies[-temp+idxzero];
        if(j != 0)
            adjacencies[j].vertex = newNumber;
        ++newNumber;
    }while(j != 0);

/*    
    for(int i = 0; i < 26; i++)
    {
        std::cout<< "Vértice: " << adjacencies[i].vertex <<std::endl;
        std::cout<< "Realidade: " << adjacencies[i].reality <<std::endl;
        std::cout<< "Desejo: " << adjacencies[i].desire <<std::endl;
        std::cout<<"\n";
    }
*/
}

Permutation *BreakpointGraph::toPermutation()
{
    int posInAdjacencies[2*n+2];
    int idxzero = n+1;

    for(int i = 0; i < 2*n+2; ++i)
    {
        posInAdjacencies[idxzero+adjacencies[i].vertex] = i;
    }

    int newElmts[n];
    int temp;
    int i = 0;
    int j = 0;
    
    while(i<n)
    {
        temp = adjacencies[adjacencies[j].reality].vertex;
        j = posInAdjacencies[-temp+idxzero];
        newElmts[i] = adjacencies[j].vertex;
        ++i;
    }
/*   
    std::cout<< "SimplePermutation: " <<std::endl;
    for(int i = 0; i < n; ++i)
        std::cout<< newElmts[i] <<std::endl;

*/
    Permutation *pA = new PermutationArray(newElmts, n);
    return pA;
}

void BreakpointGraph::simpleSort()
{
    cycles();
    while(!twoCycles.empty())
    {
        // apply 2-transposition
    }
    while(!threeCycles.empty())
    {
        
    }
    
}

/**
 * Método que retorna o número de ciclos ímpares no grafo
 */

int BreakpointGraph::oddCycles()
{
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
    int n = g->n;

    for(int i = 0; i < 2*n+2; i++)
    {
        os << g->adjacencies[i].vertex << "\t"
                << g->adjacencies[i].reality << "\t"
                << g->adjacencies[i].desire << std::endl;
    }
    return os;
}
