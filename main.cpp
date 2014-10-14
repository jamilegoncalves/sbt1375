#include <cstdlib>
#include <iostream>
#include "PermutationArray.h"
#include "PermutationTree.h"
#include "BreakpointGraph.h"

using namespace std;

int main(int argc, char** argv) {

    int elmtsA[] = { 9, 6, 1, 4, 7, 5, 2, 3, 8 };

    //int elmtsB[] = { 10, 13, 11, 12, 17, 15, 14, 16, 18 };
    
    int nA = sizeof(elmtsA)/sizeof(int);
    //int nB = sizeof(elmtsB)/sizeof(int);

    Permutation *pA = new PermutationArray(elmtsA, nA);

    //Permutation *pB =  new PermutationArray(elmtsB, nB);

    PermutationTree *treeA = new PermutationTree(pA);
    
    //PermutationTree *treeB = new PermutationTree(pB);

    std::cout<<"Build treeA:"<<std::endl;
    treeA->prettyPrint(std::cerr);

    BreakpointGraph *g = new BreakpointGraph(pA);
    
    //treeA->applyTransposition(6,7,3);

    //std::cout<<"Build treeB:"<<std::endl;
    //treeB->prettyPrint(std::cerr);

    /*
    std::pair<PermutationTree*,PermutationTree *> trees = treeA->split(4);
    trees.first->prettyPrint(cout);
    trees.second->prettyPrint(cout);
    */

    return 0;
}


