//
// File:   BreakpointGraph.h
// Author: jamile
//
// Created on 16 de Julho de 2012, 10:03
//

#include <iostream>
#include <deque>
#include "Permutation.h"

#ifndef _BREAKPOINTGRAPH_H
#define	_BREAKPOINTGRAPH_H

typedef struct
{
    int vertex;
    int reality;
    int desire;
} BPGAdjacency;

class BreakpointGraph
{
private:
    Permutation *p;
    BPGAdjacency *adjacencies;
    std::deque<BPGAdjacency *> oneCycles;
    std::deque<BPGAdjacency *> twoCycles;
    std::deque<BPGAdjacency *> threeCycles;
    std::deque<BPGAdjacency *> longCycles;

public:
    BreakpointGraph(Permutation *p);
    ~BreakpointGraph();

public:

    /**
     * Método que classifica os ciclos do grafo:
     * oneCycles, twoCycles, threeCycles and longCycles
     */
    void Cycles();

    
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
    
    //TODO:
    void toPermutation(Permutation *p);

    friend std::ostream &operator<<(std::ostream &os, BreakpointGraph *g);

};

std::ostream &operator<<(std::ostream &os, BreakpointGraph *g);

#endif	/* _BREAKPOINTGRAPH_H */