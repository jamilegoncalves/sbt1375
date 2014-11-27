/*
 * File:   PermutationArray.h
 * Author: jamile
 *
 * Created on 4 de Setembro de 2014, 15:00
 */

#ifndef PERMUTATIONARRAY_H
#define	PERMUTATIONARRAY_H
#include "Permutation.h"

class PermutationArray : public Permutation {
public:
    PermutationArray();
    PermutationArray(int elmts[], int n);
    ~PermutationArray();

    Permutation *getInverse();
    int getNumElmts();
    int getElement(int i);
    void applyTransposition(int i, int j, int k);

    /**
     * Gera uma permutação aleatória.
     * @params elmts os elementos da permutação aleatória
     * @params n quantidade de elementos
     */
    //static void randomPermutation(int *elmts, int n);
private:
    int *elmts;
    int n;
};

#endif	/* PERMUTATIONARRAY_H */
