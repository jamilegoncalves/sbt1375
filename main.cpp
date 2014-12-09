#include <algorithm>
#include <cstdlib>
#include <iostream>
#include "PermutationArray.h"
#include "PermutationTree.h"
#include "BreakpointGraph.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

void randomPermutation(int elmts[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        elmts[i] = i+1;
    }
    std::random_shuffle(elmts, elmts+n);
}

int maxN = 1000000;
int counter = 0;

void imprime_progresso(int sig) {
    std::cerr << "Progresso: " << (double)counter / (double)(maxN/10) * 100 << "%"
            << std::endl;
    alarm(10);
}

int main(int argc, char** argv) {

    //int elmtsA[] = { 9, 6, 1, 4, 7, 5, 2, 3, 8 };

    //int elmtsB[] = { 10, 13, 11, 12, 17, 15, 14, 16, 18 };
    
    //int nA = sizeof(elmtsA)/sizeof(int);
    //int nB = sizeof(elmtsB)/sizeof(int);

    //Permutation *pA = new PermutationArray(elmtsA, nA);

    //Permutation *pB =  new PermutationArray(elmtsB, nB);

    //PermutationTree *treeA = new PermutationTree(pA);
    
    //PermutationTree *treeB = new PermutationTree(pB);
/*
    std::cout<<"Build treeA:"<<std::endl;
    treeA->prettyPrint(std::cerr);
*/
    
    //BreakpointGraph *g = new BreakpointGraph(pA);
    //Permutation *simpleA = g->simplePermutation();
    
    //PermutationTree *treeA = new PermutationTree(simpleA);

    //std::cout<<"Build treeA:"<<std::endl;
    //treeA->prettyPrint(std::cerr);    
    
    //treeA->applyTransposition(6,7,3);

    //std::cout<<"Build treeB:"<<std::endl;
    //treeB->prettyPrint(std::cerr);

    /*
    std::pair<PermutationTree*,PermutationTree *> trees = treeA->split(4);
    trees.first->prettyPrint(cout);
    trees.second->prettyPrint(cout);
    */

    signal(SIGALRM, imprime_progresso);
    alarm(10);
    double *elapsedTime = new double[maxN+10]();
    int elmts[maxN+10];
    int *nperms = new int[maxN+10]();
    int n = 0;

    for(counter = 0; counter < maxN/10; ++counter)
    {
        n = ((double)rand() / (double)RAND_MAX) * maxN +10;
        //n = maxN;
        randomPermutation(elmts, n);

        PermutationArray p(elmts, n);
        
        clock_t begin = clock();
        //PermutationTree pt(&p);
        BreakpointGraph *g = new BreakpointGraph(&p);
        //Permutation *simpleA = g.simplePermutation();
        clock_t end = clock();
        delete g;

        elapsedTime[n] += double(end - begin);
        nperms[n]++;
        //delete simpleA;
        //std::cout<< "elapsedTime[" << n << "] = " << elapsedTime[n] <<endl;
    }

    int step = 1000;
    for(int i = 10; i < maxN+10; i += step)
    {
        double total = 0;
        double numperms = 0;
        for (int j=i; j<i+step; ++j) {
            total += elapsedTime[j];
            numperms += nperms[j];
        }
        if (numperms > 0)
            std::cout << i << "\t" << (total/numperms) << endl;
    }
        
    return 0;
}
