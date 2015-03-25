/* 
 * File:   Algorithms.h
 * Author: jamile
 *
 * Created on 25 de Março de 2015, 15:20
 */

#ifndef ALGORITHMS_H
#define	ALGORITHMS_H
#include "Permutation.h"
#include "PermutationTree.h"

class BreakpointGraph;

namespace Algorithms {
    int simpleSort(Permutation *p);
    
    int simpleSort(PermutationTree *p, BreakpointGraph *g);
};

#endif	/* ALGORITHMS_H */

