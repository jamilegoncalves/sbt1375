/* 
 * File:   Algorithms.cpp
 * Author: jamile
 * 
 * Created on 25 de Março de 2015, 15:20
 */

#include "Algorithms.h"
#include "BreakpointGraph.h"

using namespace Algorithms;

int Algorithms::simpleSort(Permutation *p) {
    BreakpointGraph *g = new BreakpointGraph(p);
    Permutation *simple = g->simplePermutation();
    PermutationTree *simpleTree = new PermutationTree(simple);
    BreakpointGraph *gsimple = new BreakpointGraph(simple);
    delete g;
    delete simple;
    int dist = simpleSort(simpleTree, gsimple);
    delete simpleTree;
    delete gsimple;
    return dist;
}
 
int Algorithms::simpleSort(PermutationTree *p, BreakpointGraph *g) {
    g->cycles();
    while(!g->twoCycles.empty())
    {
        // pega os dois primeiros 2 ciclos e remove da lista
        // escolhe 3 arestas
        // apply 2-transposition
        // atualiza lista de 1-cycles e 3-cycles 
    }
    while(!g->threeCycles.empty())
    {
        // seja C o primeiro 3-ciclo
        // verifique se C realmente tem 3 arestas
        //     se não tiver, remova da lista e continue 
        // remova C da lista
        // determina se C é ou não orientado
        // se C orientado,
        //    aplica 2-transposition
        //    insere três 1-ciclos na lista correta
        // senão (C não orientado),
        //     faz query em duas arestas de C para obter D
        //     se D interleave com C
        //         aplica (0,2,2)-sequencia
        //             um 0-move (não aumenta ciclos impares)
        //             um 2-move (aumenta em 2 ciclos ímpares)
        //             outro 2-move (aumenta em 2 ciclos ímpares)
        //             atualiza lista de 3-ciclos (com o 3-ciclo gerado)
        //             atualiza lista de 1-ciclos (com os três 1-ciclos gerados)
        //     senão (D não interleave com C),
        //         faz query em outras duas arestas de C para obter E
        //             se E interleave com C
        //                 aplica (0,2,2)-sequencia entre E,C
        //             senão se E interleave com D
        //                 aplica (0,2,2)-sequencia entre D,E
        //             senão
        //                 aplica (0,2,2)-sequencia envolvendo C,D,E
        //                     isto gera um novo 3-ciclo e seis 1-ciclos
    }
}