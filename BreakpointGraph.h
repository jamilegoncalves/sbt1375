//
// File:   BreakpointGraph.h
// Author: jamile
//
// Created on 16 de Julho de 2012, 10:03
//

#include <iostream>
#include <deque>
#include "Permutation.h"
#include "AdjacencyList.h"
#include "Algorithms.h"

#ifndef _BREAKPOINTGRAPH_H
#define	_BREAKPOINTGRAPH_H

class BreakpointGraph
{
private:
    int n;
    int sizeTable;
    BPG::AdjacencyList *adjlist;
    std::deque<BPG::Adjacency *> oneCycles;
    std::deque<BPG::Adjacency *> twoCycles;
    std::deque<BPG::Adjacency *> threeCycles;
    std::deque<BPG::Adjacency *> longCycles;
    
    Permutation *debug;

public:
    BreakpointGraph(Permutation *p);
    ~BreakpointGraph();

public:
    BPG::Adjacency &followRealityEdge(BPG::Adjacency &adj);
    BPG::Adjacency &followDesireEdge(BPG::Adjacency &adj);

    /**
     * Método que classifica os ciclos do grafo:
     * oneCycles, twoCycles, threeCycles and longCycles
     */
    void cycles();
    
    /**
     * Método que retorna o número de ciclos ímpares no grafo
     */

    int oddCycles();

    /**
     * Método que calcula o limite inferior da distância de transposição
     */

    int transpositionDistanceLowerBound();

    /**
     * Método que calcula o limite superior da distância de transposição
     */

    int transpositionDistanceUpperBound();

    void simpleBreakpointGraph();
    
    void renumber();
    
    Permutation *toPermutation();
    
    Permutation *simplePermutation();

    friend std::ostream &operator<<(std::ostream &os, BreakpointGraph *g);

    friend int Algorithms::simpleSort(PermutationTree *, BreakpointGraph *);

};

std::ostream &operator<<(std::ostream &os, BreakpointGraph *g);

#endif	/* _BREAKPOINTGRAPH_H */
