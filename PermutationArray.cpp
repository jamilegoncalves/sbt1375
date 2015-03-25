/*
 * File:   PermutationArray.cpp
 * Author: jamile
 *
 * Created on 4 de Setembro de 2014, 15:00
 */

#include "PermutationArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <iostream>

PermutationArray::PermutationArray()
{
    elmts = NULL;
    n = 0;
}

PermutationArray::PermutationArray(int elmts[], int n)
{
    this->elmts = new element_t[n];
    this->n = n;
    for(int i = 0; i<n; ++i)
        this->elmts[i] = elmts[i];
}

PermutationArray::~PermutationArray()
{
    delete elmts;
}

Permutation *PermutationArray::getInverse()
{
    PermutationArray *ret = new PermutationArray();
    ret->n = n;
    ret->elmts = inverse(elmts, n);
    return ret;
}

int PermutationArray::getNumElmts()
{
    return n;
}


element_t PermutationArray::getElement(int i)
{
    if (i==0)
        return 0;
    else if (i >= n+1)
        return n+1;
    else
        return elmts[i-1];
}

void PermutationArray::applyTransposition(int i, int j, int k) {
    size_t leftBlockSize = j-i;
    size_t rightBlockSize = k-j;
    size_t tmpSize = leftBlockSize + rightBlockSize;
    element_t *tmp = new element_t[tmpSize];
    memcpy(tmp, &elmts[j-1], rightBlockSize*sizeof(element_t));
    memcpy(tmp+rightBlockSize, &elmts[i-1], leftBlockSize*sizeof(element_t));
    memcpy(&elmts[i-1], tmp, tmpSize*sizeof(element_t));
    delete tmp;
}
