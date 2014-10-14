#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Permutation.h"

int* Permutation::inverse(int *p, int n)
{
    int *inv = new int[n];
    for(int i=0; i < n; ++i)
        inv[p[i]-1] = i+1;

    return inv;
}

