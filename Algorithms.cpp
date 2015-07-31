/*
 * File:   Algorithms.cpp
 * Author: jamile
 * 
 * Created on 25 de Março de 2015, 15:20
 */

#include "Algorithms.h"
#include "PermutationTree.h"
#include "BreakpointGraph.h"
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

int Algorithms::length(BreakpointGraph *g, BPG::Adjacency *cycle)
{
    int length = 0;
    Adjacency current = *cycle, first = *cycle;

    do
    {
        current = g->followDesireEdge(current);
        current = g->followRealityEdge(current);
        ++length;
    }
    while(current.vertex != first.vertex);
    
    return length;
}


bool Algorithms::isOriented(BreakpointGraph *g, PermutationTree *p, Adjacency *cycle)
{
    Adjacency *pi_iMinus1 = cycle;
    int idxiMinus1 = p->indexOf(abs(pi_iMinus1->vertex));
    Adjacency *pi_i = &g->followRealityEdge(*pi_iMinus1);
    int idxi = p->indexOf(abs(pi_i->vertex));

    // ensure we're always obtaining an adjacency with the reality edge to
    // the right
    if (idxiMinus1 > idxi) {
        std::swap(idxiMinus1, idxi);
        std::swap(pi_i, pi_iMinus1);
    }

    Adjacency *pi_jMinus1 = &g->followDesireEdge(*pi_i);
    Adjacency *pi_j = &g->followRealityEdge(*pi_jMinus1);
    int idxj = p->indexOf(abs(pi_j->vertex));
    
    Adjacency *pi_kMinus1 = &g->followDesireEdge(*pi_j);
    Adjacency *pi_k = &g->followRealityEdge(*pi_kMinus1);
    int idxk = p->indexOf(abs(pi_k->vertex));

    if( ((idxi < idxj) && (idxj < idxk)) ||
        ((idxk < idxi) && (idxi < idxj)) ||
        ((idxj < idxk) && (idxk < idxi)) ) {
        return false;
    }
    else
        return true;
}

bool Algorithms::interleave(int i, int j, int k, int x, int y, int z)
{
    if ( ((i < x) && (j < y) && (k < z)) 
            || ((x < i) && (y < j) && (z < k)) )
        return true;
    else
       return false;
}

void Algorithms::sort2ints(int &a, int &b) {
    if (b < a)
        std::swap(a,b);
}

void Algorithms::sort3ints(int &i, int &j, int &k) {
    if (i > j) {
        std::swap(i, j);
    }
    if (j > k) {
        std::swap(k, j);
    }
    if (i > j) {
        std::swap(i, j);
    }
}

/*
void updateAdj_OrientedCycle(PermutationTree *p, int a, int b, int c, 
               Adjacency *adj_a, Adjacency *adj_b, Adjacency *adj_c)
{
    int pi_a = p->getElement(a);
    int pi_cMinus1 = p->getElement(c-1);
    adj_a->vertex = pi_a;
    adj_a->reality = pi_cMinus1;
    adj_a->desire = pi_cMinus1;

    int pi_b = p->getElement(b);
    int pi_aMinus1 = p->getElement(a-1);
    adj_b->vertex = pi_b;
    adj_b->reality = pi_aMinus1;
    adj_b->desire = pi_aMinus1;
                
    int pi_c = p->getElement(c);
    int pi_bMinus1 = p->getElement(b-1);
    adj_c->vertex = pi_c;
    adj_c->reality = pi_bMinus1;
    adj_c->desire = pi_bMinus1;
}

void updateAdj_UnorientedCycle(PermutationTree *p, int a, int b, int c, 
               Adjacency *adj_a, Adjacency *adj_b, Adjacency *adj_c)
{
    int pi_a = p->getElement(a);
    int pi_bMinus1 = p->getElement(b-1);
    adj_a->vertex = pi_a;
    adj_a->reality = pi_bMinus1;
    adj_a->desire = pi_bMinus1;

    int pi_b = p->getElement(b);
    int pi_cMinus1 = p->getElement(c-1);
    adj_b->vertex = pi_b;
    adj_b->reality = pi_cMinus1;
    adj_b->desire = pi_cMinus1;

    int pi_c = p->getElement(c);
    int pi_aMinus1 = p->getElement(a-1);
    adj_c->vertex = pi_c;
    adj_c->reality = pi_aMinus1;
    adj_c->desire = pi_aMinus1;
}
*/

void updateAdj_OrientedCycle(PermutationTree *p, int a, int b, int c, 
            Adjacency *adj_a, Adjacency *adj_b, Adjacency *adj_c, Adjacency *adj_aMinus1, Adjacency *adj_bMinus1, Adjacency *adj_cMinus1)
{
    int newa = a+c-b;
    int newb = a;
    int newc = c;
    
    a = newa;
    b = newb;
    c = newc;
        
    int pi_a = -p->getElement(a);
    int pi_aMinus1 = p->getElement(a-1);
    adj_a->vertex = pi_a;
    adj_a->reality = pi_aMinus1;
    adj_a->desire = pi_aMinus1;
    adj_aMinus1->vertex = pi_aMinus1;
    adj_aMinus1->reality = pi_a;
    adj_aMinus1->desire = pi_a;

    int pi_b = -p->getElement(b);
    int pi_bMinus1 = p->getElement(b-1);
    adj_b->vertex = pi_b;
    adj_b->reality = pi_bMinus1;
    adj_b->desire = pi_bMinus1;
    adj_bMinus1->vertex = pi_bMinus1;
    adj_bMinus1->reality = pi_b;
    adj_bMinus1->desire = pi_b;
                
    int pi_c = -p->getElement(c);
    int pi_cMinus1 = p->getElement(c-1);
    adj_c->vertex = pi_c;
    adj_c->reality = pi_cMinus1;
    adj_c->desire = pi_cMinus1;
    adj_cMinus1->vertex = pi_cMinus1;
    adj_cMinus1->reality = pi_c;
    adj_cMinus1->desire = pi_c;
}

void updateAdj_UnorientedCycle(PermutationTree *p, int a, int b, int c, 
               Adjacency *adj_a, Adjacency *adj_b, Adjacency *adj_c)
{
    int pi_a = p->getElement(a);
    int pi_bMinus1 = p->getElement(b-1);
    adj_a->vertex = pi_a;
    adj_a->reality = pi_bMinus1;
    adj_a->desire = pi_bMinus1;

    int pi_b = p->getElement(b);
    int pi_cMinus1 = p->getElement(c-1);
    adj_b->vertex = pi_b;
    adj_b->reality = pi_cMinus1;
    adj_b->desire = pi_cMinus1;

    int pi_c = p->getElement(c);
    int pi_aMinus1 = p->getElement(a-1);
    adj_c->vertex = pi_c;
    adj_c->reality = pi_aMinus1;
    adj_c->desire = pi_aMinus1;
}

int Algorithms::simpleSort(PermutationTree *p, BreakpointGraph *g) {

    g->cycles();
    int dist = 0;

    Adjacency *cycle1;
    Adjacency *cycle2;

    AdjacencyListIterator it(g->adjlist);
    
    
    //Adjacency *adj_i, *adj_j, *adj_k;
    int i, j, k, l;
    //Adjacency *adj_x, *adj_y, *adj_z;
    int x, y, z;
    //Adjacency *adj_q, *adj_r, *adj_s;
    int q, r, s;

    // Ciclos de tamanho 2:
    
    while(!g->twoCycles.empty())
    {
        //g->adjlist->print(std::cout);

        // pega os dois primeiros 2-ciclos e remove da lista
        cycle1 = g->twoCycles.front(); // O(1)
        g->twoCycles.pop_front(); // O(1)

        cycle2 = g->twoCycles.front(); // O(1)
        g->twoCycles.pop_front(); // O(1)
        
        // escolhe 3 arestas
        i = p->indexOf(abs(cycle1->reality)); // O(log n)
        j = p->indexOf(abs(cycle1->desire)); // O(log n)
        sort2ints(i,j);
        k = p->indexOf(abs(cycle2->reality)); // O(log n)
        l = p->indexOf(abs(cycle2->desire)); // O(log n)
        sort2ints(k,l);
        
        sort3ints(i, j, k);
        
        
        Adjacency &adj_i = (*(g->adjlist))[-p->getElement(i)]; // O(log n)
        Adjacency &adj_iMinus1 = (*(g->adjlist))[p->getElement(i-1)]; // O(log n)
        Adjacency &adj_j = (*(g->adjlist))[-p->getElement(j)]; // O(log n)
        Adjacency &adj_jMinus1 = (*(g->adjlist))[p->getElement(j-1)]; // O(log n)
        Adjacency &adj_k = (*(g->adjlist))[-p->getElement(k)]; // O(log n)
        Adjacency &adj_kMinus1 = (*(g->adjlist))[p->getElement(k-1)]; // O(log n)
        Adjacency &adj_l = (*(g->adjlist))[-p->getElement(l)]; // O(log n)
        Adjacency &adj_lMinus1 = (*(g->adjlist))[p->getElement(l-1)]; // O(log n)
        
        p->applyTransposition(i, j, k); // O(log n)
        std::cout<<"Transposition (" << i << " , " << j
                << " , " << k << ")"<<std::endl;
        //p->prettyPrint(std::cerr);
        ++dist;
        
        int newi = i+k-j;
        int newj = i;
        int newk = k;
        int newl = l+k-j;
        
        i = newi;
        j = newj;
        k = newk;
        l = newl;
        
        int pi_iMinus1 = p->getElement(i-1);
        adj_i.reality = pi_iMinus1;
        int pi_jMinus1 = p->getElement(j-1);
        adj_j.reality = pi_jMinus1;
        int pi_kMinus1 = p->getElement(k-1);
        adj_k.reality = pi_kMinus1;
        int pi_lMinus1 = p->getElement(l-1);
        adj_l.reality = pi_lMinus1;
        
        adj_iMinus1.vertex = pi_iMinus1;
        adj_jMinus1.vertex = pi_jMinus1;
        adj_kMinus1.vertex = pi_kMinus1;
        adj_lMinus1.vertex = pi_lMinus1;
        
        int pi_i = -p->getElement(i);
        int pi_j = -p->getElement(j);
        int pi_k = -p->getElement(k);
        int pi_l = -p->getElement(l);
        
        adj_iMinus1.reality = pi_j;//pi_j
        adj_jMinus1.reality = pi_k;//pi_k
        adj_kMinus1.reality = pi_i;//pi_i
        adj_lMinus1.reality = pi_l;
        
        adj_i.desire = pi_lMinus1;
        adj_j.desire = pi_iMinus1;
        adj_k.desire = pi_kMinus1;
        adj_l.desire = pi_jMinus1;
        
        adj_iMinus1.desire = pi_l;//pi_l
        adj_jMinus1.desire = pi_k;//pi_k
        adj_kMinus1.desire = pi_j;//pi_j
        adj_lMinus1.desire = pi_i;
       
        g->adjlist->print(std::cout);
        
        g->threeCycles.push_back(&adj_i);
        g->oneCycles.push_back(&adj_k);

        //g->adjlist->print(std::cout);
        
        /*
        std::cout<<"Adj_i"<<adj_i.vertex<<","<<adj_i.reality<<","<<adj_i.desire<<std::endl;
        std::cout<<"Adj_j"<<adj_j.vertex<<","<<adj_j.reality<<","<<adj_j.desire<<std::endl;
        std::cout<<"Adj_k"<<adj_k.vertex<<","<<adj_k.reality<<","<<adj_k.desire<<std::endl;
        std::cout<<"Adj_l"<<adj_l.vertex<<","<<adj_l.reality<<","<<adj_l.desire<<std::endl;

        std::cout<<"Adj_iMinus1"<<adj_iMinus1.vertex<<","<<adj_iMinus1.reality<<","<<adj_iMinus1.desire<<std::endl;
        std::cout<<"Adj_jMinus1"<<adj_jMinus1.vertex<<","<<adj_jMinus1.reality<<","<<adj_jMinus1.desire<<std::endl;
        std::cout<<"Adj_kMinus1"<<adj_kMinus1.vertex<<","<<adj_kMinus1.reality<<","<<adj_kMinus1.desire<<std::endl;
        std::cout<<"Adj_lMinus1"<<adj_lMinus1.vertex<<","<<adj_lMinus1.reality<<","<<adj_lMinus1.desire<<std::endl;
        */

        //test
        //g->threeCycles.pop_front();
        //std::cout<<"size:"<<g->threeCycles.size()<<std::endl;
        //g->threeCycles.pop_front();
/*        
        it.setTo(g->threeCycles.back()->vertex);

        
        int prim = it.get().vertex;
        
        std::cout<<"Adj"<<it.get().vertex<<","<<it.get().reality<<","<<it.get().desire<<std::endl;
        
        do
        {
            it.nextDesire();
            std::cout<<"Adj"<<it.get().vertex<<","<<it.get().reality<<","<<it.get().desire<<std::endl;
            it.nextReality();
            std::cout<<"Adj"<<it.get().vertex<<","<<it.get().reality<<","<<it.get().desire<<std::endl;            
        }while(it.get().vertex != prim);
*/
/*
        int pi_iMinus1 = p->getElement(i-1);
        int pi_i = p->getElement(i);
        int pi_j = p->getElement(j);
        adj_i->vertex = pi_iMinus1;
        adj->reality = -pi_i;
        adj->desire = pi_j;
        
        g->threeCycles.push_back(adj);        
       
        int pi_kMinus1 = p->getElement(k-1);
        int pi_k = -(p->getElement(k));
        adj->vertex = pi_kMinus1;
        adj->reality = pi_k;
        adj->desire =  pi_k;
        
        g->oneCycles.push_back(adj);
  */
        
/*        
        // two 2-cycles cases
        if (k < i && i < l && l < j) {
            // case 1:
            //             __________
            //            /  ______  \
            //     __________      \  \
            //    /  ______  \      \  \
            //   /  /  /  /\  \      \  \
            //  /__/  /__/  \__\      \__\
            //   k     i      l         j
            p->applyTransposition(k, i, l); // O(log n)
            // atualiza lista de 1-cycles e 3-cycles
            g->oneCycles.push_back(cycle1);
            g->threeCycles.push_back(cycle2);
            
        } else if (i < k && k < j && j < l) {
            // case 2:
            //             __________
            //            /  ______  \
            //     __________      \  \
            //    /  ______  \      \  \
            //   /  /  /  /\  \      \  \
            //  /__/  /__/  \__\      \__\
            //   i     k      j         l
            p->applyTransposition(i, k, j); // O(log n)
            // atualiza lista de 1-cycles e 3-cycles
            g->oneCycles.push_back(cycle1);
            g->threeCycles.push_back(cycle2);
            
        } else if (j < k) {
            // case 3:
            //     __________        __________          
            //    /  ______  \      /  ______  \      
            //   /  /      \  \    /  /      \  \         
            //  /__/        \__\  /__/        \__\         
            //   i            j    k            l
            p->applyTransposition(i, j, k); // O(log n)
            // atualiza lista de 1-cycles e 3-cycles
            g->oneCycles.push_back(cycle1);
            g->threeCycles.push_back(cycle2);
                        
        } else if (l < i) {
            // case 4:
            //     __________        __________          
            //    /  ______  \      /  ______  \      
            //   /  /      \  \    /  /      \  \         
            //  /__/        \__\  /__/        \__\         
            //   k            l    i            j
            p->applyTransposition(k, l, i); // O(log n)
            // atualiza lista de 1-cycles e 3-cycles
            g->oneCycles.push_back(cycle1);
            g->threeCycles.push_back(cycle2);
            
        } else if (i < k) {
            // case 5:
            //      ___________________
            //     /  _______________  \
            //    /  /   __________  \  \
            //   /  /   /  ______  \  \  \
            //  /  /   /  /      \  \  \  \
            // /__/   /__/        \__\  \__\
            //  i      k            l     j
            p->applyTransposition(i, k, l); // O(log n)
            // atualiza lista de 1-cycles e 3-cycles
            g->oneCycles.push_back(cycle1);
            g->threeCycles.push_back(cycle2);            

        } else {
            // case 6:
            //      ___________________
            //     /  _______________  \
            //    /  /   __________  \  \
            //   /  /   /  ______  \  \  \
            //  /  /   /  /      \  \  \  \
            // /__/   /__/        \__\  \__\
            //  k      i            j     l
            p->applyTransposition(k, i, j); // O(log n)
            // atualiza lista de 1-cycles e 3-cycles
            g->oneCycles.push_back(cycle1);
            g->threeCycles.push_back(cycle2);            
        }
 */
    }
    
    // Ciclos de tamanho 3:
    while(!g->threeCycles.empty())
    {
        //g->adjlist->print(std::cout);

        // seja C o primeiro 3-ciclo
        cycle1 = g->threeCycles.front();
        g->threeCycles.pop_front();
        
        //p->prettyPrint(std::cerr);
  /*      
        it.setTo(cycle1->vertex);
        
        int prim = it.get().vertex;
        
            std::cout<<"Adj"<<it.get().vertex<<","<<it.get().reality<<","<<it.get().desire<<std::endl;
        
        do
        {
            it.nextDesire();
            std::cout<<"Adj"<<it.get().vertex<<","<<it.get().reality<<","<<it.get().desire<<std::endl;
            it.nextReality();
            std::cout<<"Adj"<<it.get().vertex<<","<<it.get().reality<<","<<it.get().desire<<std::endl;            
        }while(it.get().vertex != prim);
        
    */    
        // Se C realmente tem 3 arestas
        if(length(g, cycle1) == 3)
        {
            // i, j, k são as 3 arestas do ciclo C:
            it.setTo(cycle1->vertex);
            i = p->indexOf(abs(it.get().reality));
            it.nextReality();
            it.nextDesire();
            j = p->indexOf(abs(it.get().reality));
            it.nextReality();
            it.nextDesire();                
            k = p->indexOf(abs(it.get().reality));

            sort3ints(i, j, k);
            
            Adjacency &adj_i = (*(g->adjlist))[-p->getElement(i)]; // O(log n)
            Adjacency &adj_j = (*(g->adjlist))[-p->getElement(j)]; // O(log n)
            Adjacency &adj_k = (*(g->adjlist))[-p->getElement(k)]; // O(log n)
            Adjacency &adj_iMinus1 = (*(g->adjlist))[-p->getElement(i-1)]; // O(log n)
            Adjacency &adj_jMinus1 = (*(g->adjlist))[-p->getElement(j-1)]; // O(log n)
            Adjacency &adj_kMinus1 = (*(g->adjlist))[-p->getElement(k-1)]; // O(log n)
                        
            // Se C é orientado
            if(isOriented(g, p, cycle1))
            {                
                // apply 2-transposition
                std::cout << "antes:" << std::endl;
                g->adjlist->print(std::cout);
                std::cout.flush();

                p->applyTransposition(i, j, k);
                std::cout<<"Transposition (" << i << " , " << j
                        << " , " << k << ")"<<std::endl;
                //p->prettyPrint(std::cerr);
                ++dist;
                updateAdj_OrientedCycle(p, i, j, k, &adj_i, &adj_j, &adj_k, &adj_iMinus1, &adj_jMinus1, &adj_kMinus1);

                std::cout << "depois:" << std::endl;
                g->adjlist->print(std::cout);
                std::cout.flush();
                //x''
                /*                
                int pi_i = p->getElement(i);
                int pi_kMinus1 = p->getElement(k-1);
                adj_i.vertex = pi_i;
                adj_i.reality = pi_kMinus1;
                adj_i.desire = pi_kMinus1;

                int pi_j = p->getElement(j);
                int pi_iMinus1 = p->getElement(i-1);
                adj_j.vertex = pi_j;
                adj_j.reality = pi_iMinus1;
                adj_j.desire = pi_iMinus1;
                
                int pi_k = p->getElement(k);
                int pi_jMinus1 = p->getElement(j-1);
                adj_k.vertex = pi_k;
                adj_k.reality = pi_jMinus1;
                adj_k.desire = pi_jMinus1;
*/               

                g->adjlist->print(std::cout);
                
                // Terei três 1-ciclos
                g->oneCycles.push_back(&adj_i);
                g->oneCycles.push_back(&adj_j);
                g->oneCycles.push_back(&adj_k);
 
            }
            else // Senão (C não orientado) 
            {
                // Faz query em duas arestas de C para obter D
                // x, y, z são as 3 arestas do ciclo D:
                x =  p->query(i, j);                    
                int pi_x = p->getElement(x);
                
                int yminus1 = p->indexOf(abs(pi_x - 1));
                y =  yminus1 + 1;
                int pi_y = p->getElement(y);
                
                int zminus1 = p->indexOf(abs(pi_y - 1));
                z = zminus1 + 1;

                sort3ints(x, y, z);

                Adjacency &adj_x = (*(g->adjlist))[p->getElement(x)]; // O(log n)
                Adjacency &adj_y = (*(g->adjlist))[p->getElement(y)]; // O(log n)
                Adjacency &adj_z = (*(g->adjlist))[p->getElement(z)]; // O(log n)                                            
                Adjacency &adj_xMinus1 = (*(g->adjlist))[p->getElement(x-1)]; // O(log n)
                Adjacency &adj_yMinus1 = (*(g->adjlist))[p->getElement(y-1)]; // O(log n)
                Adjacency &adj_zMinus1 = (*(g->adjlist))[p->getElement(z-1)]; // O(log n) 
                
                // Se C interleave com D
                if( interleave(i, j, k, x, y, z) )
                {
                    // Aplica (0,2,2)-sequencia:
                    
                    // 0-move: (não aumenta ciclos impares)
                    p->applyTransposition(i, j, k);
                    std::cout<<"Transposition (" << i << " , " << j
                            << " , " << k << ")"<<std::endl;
                    p->prettyPrint(std::cerr);
                    ++dist;
                    
                    // 2-move: (aumenta em 2 ciclos ímpares)
                    int newx = i+y-j;
                    int newy = k-j+x;
                    int newz = z;
                    x = newx;
                    y = newy;
                    z = newz;
                    
                    p->applyTransposition(x, y, z);
                    std::cout<<"Transposition (" << i << " , " << j
                            << " , " << k << ")"<<std::endl;                    
                    p->prettyPrint(std::cerr);
                    ++dist;
                    
                    // 2-move: (aumenta em 2 ciclos ímpares)
                    newx = i;
                    newy = i+y-x;
                    newz = i-x+z;
                    x = newx;
                    y = newy;
                    z = newz;

                    p->applyTransposition(x, y, z);
                    std::cout<<"Transposition (" << i << " , " << j
                            << " , " << k << ")"<<std::endl;
                    p->prettyPrint(std::cerr);
                    ++dist;
    
                    updateAdj_UnorientedCycle(p, i, j, k, &adj_i, &adj_j, &adj_k);
                    updateAdj_UnorientedCycle(p, x, y, z, &adj_x, &adj_y, &adj_z);                    
/*                    
                    int pi_i = p->getElement(i);
                    int pi_jMinus1 = p->getElement(j-1);
                    adj_i.vertex = pi_i;
                    adj_i.reality = pi_jMinus1;
                    adj_i.desire = pi_jMinus1;

                    int pi_j = p->getElement(j);
                    int pi_kMinus1 = p->getElement(k-1);
                    adj_j.vertex = pi_j;
                    adj_j.reality = pi_kMinus1;
                    adj_j.desire = pi_kMinus1;

                    int pi_k = p->getElement(k);
                    int pi_iMinus1 = p->getElement(i-1);
                    adj_k.vertex = pi_k;
                    adj_k.reality = pi_iMinus1;
                    adj_k.desire = pi_iMinus1;

                    int pi_x = p->getElement(x);
                    int pi_yMinus1 = p->getElement(y-1);
                    adj_x.vertex = pi_x;
                    adj_x.reality = pi_yMinus1;
                    adj_x.desire = pi_yMinus1;

                    int pi_y = p->getElement(y);
                    int pi_zMinus1 = p->getElement(z-1);
                    adj_y.vertex = pi_y;
                    adj_y.reality = pi_zMinus1;
                    adj_y.desire = pi_zMinus1;


                    int pi_z = p->getElement(z);
                    int pi_xMinus1 = p->getElement(x-1);
                    adj_z.vertex = pi_z;
                    adj_z.reality = pi_xMinus1;
                    adj_z.desire = pi_xMinus1;
*/
                    g->adjlist->print(std::cout);
                    
                    // Terei seis 1-ciclos
                    g->oneCycles.push_back(&adj_i);
                    g->oneCycles.push_back(&adj_j);
                    g->oneCycles.push_back(&adj_k);
                    g->oneCycles.push_back(&adj_x);
                    g->oneCycles.push_back(&adj_y);
                    g->oneCycles.push_back(&adj_z);
                }
                else // Senão (C não interleave com D)
                {
                    // Faz query em outras duas arestas de C para obter E
                    // q, r, s são as 3 arestas do ciclo E:
                    q =  p->query(i, j);
                    int pi_q = p->getElement(q);

                    int rminus1 = p->indexOf(abs(pi_q - 1));
                    r =  rminus1 + 1;
                    int pi_r = p->getElement(r);

                    int sminus1 = p->indexOf(abs(pi_r - 1));
                    s = sminus1 + 1;
                    
                    sort3ints(q, r, s);
                    
                    if ( interleave(i, j, k, q, r, s) ) // Se C interleave com E
                    {
                        // Aplica (0,2,2)-sequencia entre C, E
                        
                        // 0-move: (não aumenta ciclos impares)
                        p->applyTransposition(i, j, k);
                        std::cout<<"Transposition (" << i << " , " << j
                                << " , " << k << ")"<<std::endl;                        
                        p->prettyPrint(std::cerr);
                        ++dist;
                        
                        // 2-move: (aumenta em 2 ciclos ímpares)
                        int newq = i+r-j;
                        int newr = k-j+q;
                        int news = s;
                        q = newq;
                        r = newr;
                        s = news;

                        p->applyTransposition(q, r, s);
                        std::cout<<"Transposition (" << i << " , " << j
                                << " , " << k << ")"<<std::endl;
                        p->prettyPrint(std::cerr);
                        ++dist;
                        
                        // 2-move: (aumenta em 2 ciclos ímpares)
                        newq = i;
                        newr = i+r-q;
                        news = i-q+s;
                        q = newq;
                        r = newr;
                        s = news;
                        p->applyTransposition(q, r, s);
                        std::cout<<"Transposition (" << i << " , " << j
                                << " , " << k << ")"<<std::endl;
                        p->prettyPrint(std::cerr);
                        ++dist;

                        updateAdj_UnorientedCycle(p, i, j, k, &adj_i, &adj_j, &adj_k);                        
/*                        
                        int pi_i = p->getElement(i);
                        int pi_jMinus1 = p->getElement(j-1);
                        adj_i.vertex = pi_i;
                        adj_i.reality = pi_jMinus1;
                        adj_i.desire = pi_jMinus1;

                        int pi_j = p->getElement(j);
                        int pi_kMinus1 = p->getElement(k-1);
                        adj_j.vertex = pi_j;
                        adj_j.reality = pi_kMinus1;
                        adj_j.desire = pi_kMinus1;

                        int pi_k = p->getElement(k);
                        int pi_iMinus1 = p->getElement(i-1);
                        adj_k.vertex = pi_k;
                        adj_k.reality = pi_iMinus1;
                        adj_k.desire = pi_iMinus1;
*/
                        int pi_q = p->getElement(q);
                        Adjacency &adj_q = (*(g->adjlist))[pi_q];
                        int pi_rMinus1 = p->getElement(r-1);
                        adj_q.vertex = pi_q;
                        adj_q.reality = pi_rMinus1;
                        adj_q.desire = pi_rMinus1;

                        int pi_r = p->getElement(r);
                        Adjacency &adj_r = (*(g->adjlist))[pi_r];
                        int pi_sMinus1 = p->getElement(s-1);
                        adj_r.vertex = pi_r;
                        adj_r.reality = pi_sMinus1;
                        adj_r.desire = pi_sMinus1;

                        int pi_s = p->getElement(s);
                        Adjacency &adj_s = (*(g->adjlist))[pi_s];
                        int pi_qMinus1 = p->getElement(q-1);
                        adj_s.vertex = pi_s;
                        adj_s.reality = pi_qMinus1;
                        adj_s.desire = pi_qMinus1;
                      
                        g->adjlist->print(std::cout);
                        
                        // Terei seis 1-ciclos
                        g->oneCycles.push_back(&adj_i);
                        g->oneCycles.push_back(&adj_j);
                        g->oneCycles.push_back(&adj_k);
                        g->oneCycles.push_back(&adj_q);
                        g->oneCycles.push_back(&adj_r);
                        g->oneCycles.push_back(&adj_s);
                    }
                    else if ( interleave(x, y, z, q, r, s) ) // Senão se D interleave com E
                    {
                        // Aplica (0,2,2)-sequencia entre D,E

                        // 0-move: (não aumenta ciclos impares)
                        p->applyTransposition(x, y, z);
                        std::cout<<"Transposition (" << i << " , " << j
                                << " , " << k << ")"<<std::endl;
                        p->prettyPrint(std::cerr);
                        ++dist;
                        
                        // 2-move: (aumenta em 2 ciclos ímpares)
                        int newq = x+r-y;
                        int newr = z-y+q;
                        int news = s;
                        q = newq;
                        r = newr;
                        s = news;

                        p->applyTransposition(q, r, s);
                        std::cout<<"Transposition (" << i << " , " << j
                                << " , " << k << ")"<<std::endl;
                        p->prettyPrint(std::cerr);
                        ++dist;
                        
                        // 2-move: (aumenta em 2 ciclos ímpares)
                        newq = x;
                        newr = x+r-q;
                        news = x-q+s;
                        q = newq;
                        r = newr;
                        s = news;

                        p->applyTransposition(q, r, s);                        
                        std::cout<<"Transposition (" << i << " , " << j
                                << " , " << k << ")"<<std::endl;
                        p->prettyPrint(std::cerr);
                        ++dist;

                        updateAdj_UnorientedCycle(p, x, y, z, &adj_x, &adj_y, &adj_z);
//                        updateAdj_UnorientedCycle(p, q, r, s, &adj_q, &adj_r, &adj_s);                    
                        
/*                        
                        int pi_x = p->getElement(x);
                        int pi_yMinus1 = p->getElement(y-1);
                        adj_x.vertex = pi_x;
                        adj_x.reality = pi_yMinus1;
                        adj_x.desire = pi_yMinus1;

                        int pi_y = p->getElement(y);
                        int pi_zMinus1 = p->getElement(z-1);
                        adj_y.vertex = pi_y;
                        adj_y.reality = pi_zMinus1;
                        adj_y.desire = pi_zMinus1;

                        int pi_z = p->getElement(z);
                        int pi_xMinus1 = p->getElement(x-1);
                        adj_z.vertex = pi_z;
                        adj_z.reality = pi_xMinus1;
                        adj_z.desire = pi_xMinus1;
*/
                        int pi_q = p->getElement(q);
                        Adjacency &adj_q = (*(g->adjlist))[pi_q];
                        int pi_rMinus1 = p->getElement(r-1);
                        adj_q.vertex = pi_q;
                        adj_q.reality = pi_rMinus1;
                        adj_q.desire = pi_rMinus1;

                        int pi_r = p->getElement(r);
                        Adjacency &adj_r = (*(g->adjlist))[pi_r];
                        int pi_sMinus1 = p->getElement(s-1);
                        adj_r.vertex = pi_r;
                        adj_r.reality = pi_sMinus1;
                        adj_r.desire = pi_sMinus1;

                        int pi_s = p->getElement(s);
                        Adjacency &adj_s = (*(g->adjlist))[pi_s];
                        int pi_qMinus1 = p->getElement(q-1);
                        adj_s.vertex = pi_s;
                        adj_s.reality = pi_qMinus1;
                        adj_s.desire = pi_qMinus1;

                        g->adjlist->print(std::cout);
                        
                        // Terei seis 1-ciclos
                        g->oneCycles.push_back(&adj_x);
                        g->oneCycles.push_back(&adj_y);
                        g->oneCycles.push_back(&adj_z);
                        g->oneCycles.push_back(&adj_q);
                        g->oneCycles.push_back(&adj_r);
                        g->oneCycles.push_back(&adj_s);
                    }
                    else // Senão
                    {
                        // Aplica (0,2,2)-sequencia envolvendo C,D,E:
                        Adjacency &adj_q = (*(g->adjlist))[p->getElement(q)];
                        
                        // Se D é orientado
                        if(isOriented(g, p, &adj_x))
                        {
                            // Inserir C e E no fim da lista
                            g->threeCycles.push_back(&adj_i);
                            g->threeCycles.push_back(&adj_q);

                            // Aplicar 2-transposition em D
                            p->applyTransposition(x, y, z);
                            std::cout<<"Transposition (" << i << " , " << j
                                    << " , " << k << ")"<<std::endl;
                            p->prettyPrint(std::cerr);
                            ++dist;
                            
                            updateAdj_OrientedCycle(p, x, y, z, &adj_x, &adj_y, &adj_z,
                                                    &adj_xMinus1, &adj_yMinus1, &adj_zMinus1);
/*                            
                            int pi_x = p->getElement(x);
                            int pi_zMinus1 = p->getElement(z-1);
                            adj_x.vertex = pi_x;
                            adj_x.reality = pi_zMinus1;
                            adj_x.desire = pi_zMinus1;

                            int pi_y = p->getElement(y);
                            int pi_xMinus1 = p->getElement(x-1);
                            adj_y.vertex = pi_y;
                            adj_y.reality = pi_xMinus1;
                            adj_y.desire = pi_xMinus1;

                            int pi_z = p->getElement(z);
                            int pi_yMinus1 = p->getElement(y-1);
                            adj_z.vertex = pi_z;
                            adj_z.reality = pi_yMinus1;
                            adj_z.desire = pi_yMinus1;
*/
                            g->adjlist->print(std::cout);
                            
                            // Terei três 1-ciclos
                            g->oneCycles.push_back(&adj_x);
                            g->oneCycles.push_back(&adj_y);
                            g->oneCycles.push_back(&adj_z);

                        }
                        else if(isOriented(g, p, &adj_q)) // Senão se E é orientado
                        {
                            // Inserir C e D no fim da lista
                            g->threeCycles.push_back(&adj_i);
                            g->threeCycles.push_back(&adj_x);
                            
                            // Aplicar 2-transposition em E
                            p->applyTransposition(q, r, s);
                            std::cout<<"Transposition (" << i << " , " << j
                                    << " , " << k << ")"<<std::endl;
                            p->prettyPrint(std::cerr);
                            ++dist;
                            
                            int pi_q = p->getElement(q);
                            int pi_sMinus1 = p->getElement(s-1);
                            Adjacency &adj_q = (*(g->adjlist))[pi_q];
                            adj_q.vertex = pi_q;
                            adj_q.reality = pi_sMinus1;
                            adj_q.desire = pi_sMinus1;

                            int pi_r = p->getElement(r);
                            int pi_qMinus1 = p->getElement(q-1);
                            Adjacency &adj_r = (*(g->adjlist))[pi_r];
                            adj_r.vertex = pi_r;
                            adj_r.reality = pi_qMinus1;
                            adj_r.desire = pi_qMinus1;

                            int pi_s = p->getElement(s);
                            int pi_rMinus1 = p->getElement(r-1);
                            Adjacency &adj_s = (*(g->adjlist))[pi_s];
                            adj_s.vertex = pi_s;
                            adj_s.reality = pi_rMinus1;
                            adj_s.desire = pi_rMinus1;

                            g->adjlist->print(std::cout);
                            
                            // Terei três 1-ciclos
                            g->oneCycles.push_back(&adj_q);
                            g->oneCycles.push_back(&adj_r);
                            g->oneCycles.push_back(&adj_s);
                        }
                        else
                        {
                            // Aplicar 0-move em C
                            // C passa a ser orientado!
                            // 0-move: (não aumenta ciclos impares)
                            p->applyTransposition(i, j, k);
                            std::cout<<"Transposition (" << i << " , " << j
                                    << " , " << k << ")"<<std::endl;
                            p->prettyPrint(std::cerr);
                            ++dist;
                            
                            if(isOriented(g, p, &adj_x)) // Se D é orientado
                            {
                                // Terei C e D orientado
                                // 2-move: (aumenta em 2 ciclos ímpares)
                                int newx = i+y-j;
                                int newy = k-j+x;
                                int newz = z;
                                x = newx;
                                y = newy;
                                z = newz;
                                p->applyTransposition(x, y, z);
                                std::cout<<"Transposition (" << i << " , " << j
                                        << " , " << k << ")"<<std::endl;                                
                                p->prettyPrint(std::cerr);
                                ++dist;
                                
                                // Aplicar 2-move em E
                                // 2-move: (aumenta em 2 ciclos ímpares)
                                int newq = i+r-j;
                                int newr = k-j+q;
                                int news = s;
                                q = newq;
                                r = newr;
                                s = news;
                                p->applyTransposition(q, r, s);
                                std::cout<<"Transposition (" << i << " , " << j
                                        << " , " << k << ")"<<std::endl;
                                p->prettyPrint(std::cerr);
                                ++dist;
                                
                                updateAdj_UnorientedCycle(p, x, y, z, &adj_x, &adj_y, &adj_z);
                                
                                int pi_q = p->getElement(q);
                                int pi_sMinus1 = p->getElement(s-1);
                                Adjacency &adj_q = (*(g->adjlist))[pi_q];
                                adj_q.vertex = pi_q;
                                adj_q.reality = pi_sMinus1;
                                adj_q.desire = pi_sMinus1;

                                int pi_r = p->getElement(r);
                                int pi_qMinus1 = p->getElement(q-1);
                                Adjacency &adj_r = (*(g->adjlist))[pi_r];
                                adj_r.vertex = pi_r;
                                adj_r.reality = pi_qMinus1;
                                adj_r.desire = pi_qMinus1;

                                int pi_s = p->getElement(s);
                                int pi_rMinus1 = p->getElement(r-1);
                                Adjacency &adj_s = (*(g->adjlist))[pi_s];
                                adj_s.vertex = pi_s;
                                adj_s.reality = pi_rMinus1;
                                adj_s.desire = pi_rMinus1;
                                
                                g->adjlist->print(std::cout);
                                
                                // Terei seis 1-ciclos
                                g->oneCycles.push_back(&adj_x);
                                g->oneCycles.push_back(&adj_y);
                                g->oneCycles.push_back(&adj_z);                                                                
                                g->oneCycles.push_back(&adj_q);
                                g->oneCycles.push_back(&adj_r);
                                g->oneCycles.push_back(&adj_s);                                                                
                            }
                            else if(isOriented(g, p, &adj_q)) // Else if E é orientado
                            {
                                // Terei C e E orientado
                                // Aplicar 2-move em E
                                // 2-move: (aumenta em 2 ciclos ímpares)
                                int newq = i+r-j;
                                int newr = k-j+q;
                                int news = s;
                                q = newq;
                                r = newr;
                                s = news;
                                p->applyTransposition(q, r, s);
                                std::cout<<"Transposition (" << i << " , " << j
                                        << " , " << k << ")"<<std::endl;
                                p->prettyPrint(std::cerr);
                                ++dist;
                                
                                // Aplicar 2-move em D
                                // 2-move: (aumenta em 2 ciclos ímpares)
                                int newx = i+y-j;
                                int newy = k-j+x;
                                int newz = z;
                                x = newx;
                                y = newy;
                                z = newz;
                                p->applyTransposition(x, y, z);
                                std::cout<<"Transposition (" << i << " , " << j
                                        << " , " << k << ")"<<std::endl;
                                p->prettyPrint(std::cerr);
                                ++dist;

                                updateAdj_UnorientedCycle(p, x, y, z, &adj_x, &adj_y, &adj_z);
                                
                                int pi_q = p->getElement(q);
                                int pi_sMinus1 = p->getElement(s-1);
                                Adjacency &adj_q = (*(g->adjlist))[pi_q];
                                adj_q.vertex = pi_q;
                                adj_q.reality = pi_sMinus1;
                                adj_q.desire = pi_sMinus1;

                                int pi_r = p->getElement(r);
                                int pi_qMinus1 = p->getElement(q-1);
                                Adjacency &adj_r = (*(g->adjlist))[pi_r];
                                adj_r.vertex = pi_r;
                                adj_r.reality = pi_qMinus1;
                                adj_r.desire = pi_qMinus1;

                                int pi_s = p->getElement(s);
                                int pi_rMinus1 = p->getElement(r-1);
                                Adjacency &adj_s = (*(g->adjlist))[pi_s];
                                adj_s.vertex = pi_s;
                                adj_s.reality = pi_rMinus1;
                                adj_s.desire = pi_rMinus1;
                                
                                g->adjlist->print(std::cout);
                                
                                // Terei seis 1-ciclos
                                g->oneCycles.push_back(&adj_x);
                                g->oneCycles.push_back(&adj_y);
                                g->oneCycles.push_back(&adj_z);                                                                
                                g->oneCycles.push_back(&adj_q);
                                g->oneCycles.push_back(&adj_r);
                                g->oneCycles.push_back(&adj_s);                                                                
                            }
                            else
                            {
                                throw (const char *)"Cannot sort!";
                            }                            
                        }
                    }
                }
            }            
        }
        else // Se não tiver, remova da lista e continue 
        {
            continue;
        }
    }
    return dist;
}