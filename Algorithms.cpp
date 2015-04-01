/*
 * File:   Algorithms.cpp
 * Author: jamile
 * 
 * Created on 25 de Março de 2015, 15:20
 */

#include "Algorithms.h"
#include "BreakpointGraph.h"
#include "PermutationTree.h"
#include <algorithm>

using namespace Algorithms;
using namespace BPG;

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

bool Algorithms::confirmCycle(Adjacency *cycle, int length)
{
    int realLength;
    AdjacencyListIterator it(adjlist);
    it.setTo(cycle->vertex);
    
    while(it.nextDesire)
    {
        it.nextReality;
        ++realLength;
    }
    
    if(realLength == length)
        return true;
    else
        return false;
}

bool Algorithms::isOriented(Adjacency *cycle)
{
    // Vou precisar dos índices dos vértices
}

void Algorithms::sort3ints(int &i, int &j, int &k) {
    if (i > j) {
        std::swap(i, j);
    }
    // aqui i < j
    if (j > k) {
        std::swap(k, j);
    }
    // aqui j < k
}

int Algorithms::simpleSort(PermutationTree *p, BreakpointGraph *g) {

    g->cycles();

    Adjacency *cycle1;
    Adjacency *cycle2;

    int i, j, k;
    
    // Ciclos de tamanho 2:
    while(!g->twoCycles.empty()) // O(n)
    {
        // pega os dois primeiros 2-ciclos e remove da lista
        cycle1 = g->twoCycles->front; // O(1)
        g->twoCycles.pop_front(); // O(1)

        cycle2 = g->twoCycles->front; // O(1)
        g->twoCycles.pop_front(); // O(1)
        
        // escolhe 3 arestas
        i = p->indexOf(cycle1->reality); // O(log n)
        j = p->indexOf(cycle1->desire); // O(log n)
        k = p->indexOf(cycle2->reality); // O(log n)

        sort3ints(i, j, k);

        // apply 2-transposition
        p->applyTransposition(i, j, k); // O(log n)
        
        // atualiza lista de 1-cycles e 3-cycles
        g->oneCycles.push_back(&cycle1);
        g->threeCycles.push_back(&cycle2);
    }
    
    // Ciclos de tamanho 3:
    while(!g->threeCycles.empty())
    {
        // seja C o primeiro 3-ciclo
        cycle1 = g->threeCycles->front;
        g->threeCycles.pop_front();
        
        cycle2 = g->threeCycles->front;
        g->threeCycles.pop_front();
        
        // Se C realmente tem 3 arestas
        if( (confirmCycle(cycle1, 3)) && (confirmCycle(cycle2, 3)) )
        {
            // Se C é orientado
            if(isOriented(cycle1))
            {                
                // escolhe 3 arestas
                i = getIndex(cycle1->reality);
                j = getIndex(cycle1->desire);
                k = getIndex(cycle2->reality);

                // apply 2-transposition
                applyTransposition(i, j, k);
                
                // Insere três 1-ciclos na lista correta
                // Terei um 3-ciclo e três 1-ciclos
                // Descobrir os 1-ciclos ??
            }
            else // Senão (C não orientado) 
            {
                // faz query em duas arestas de C para obter D
                i = getIndex(cycle1.get().reality);
                j = getIndex(cycle1.get().desire);
                k = query(i, j);// Inteiro, preciso de uma adjacência no BPG
                
                
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
        else // Se não tiver, remova da lista e continue 
        {
            continue;
        }
    }
}
