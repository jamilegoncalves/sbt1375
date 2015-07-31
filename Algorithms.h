/* 
 * File:   Algorithms.h
 * Author: jamile
 *
 * Created on 25 de Março de 2015, 15:20
 */

#ifndef ALGORITHMS_H
#define	ALGORITHMS_H
#include "AdjacencyList.h"
#include "Permutation.h"
#include "PermutationTree.h"

class BreakpointGraph;

namespace Algorithms {
    int simpleSort(Permutation *p);
    int simpleSort(PermutationTree *p, BreakpointGraph *g);
    void updateAdj_OrientedCycle(PermutationTree *p, int a, int b, int c, 
               BPG::Adjacency *&adj_a, BPG::Adjacency *&adj_b, BPG::Adjacency *&adj_c, BPG::Adjacency *adj_aMinus1, BPG::Adjacency *adj_bMinus1, BPG::Adjacency *adj_cMinus1);
    void updateAdj_UnorientedCycle(PermutationTree *p, int a, int b, int c, 
               BPG::Adjacency *&adj_a, BPG::Adjacency *&adj_b, BPG::Adjacency *&adj_c);
    int length(BreakpointGraph *g, BPG::Adjacency *cycle);
    bool isOriented(BreakpointGraph *g, PermutationTree *p, BPG::Adjacency *cycle);
    bool interleave(int i, int j, int k, int x, int y, int z);
    void sort2ints(int &a, int &b);
    void sort3ints(int &i, int &j, int &k);
};

#endif	/* ALGORITHMS_H */