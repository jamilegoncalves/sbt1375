#include <assert.h>
#include <stdlib.h>
#include "Permutation.h"

Permutation::~Permutation()
{
}

int* Permutation::inverse(int *p, int n)
{
    int *inv = new int[n];
    for(int i=0; i < n; ++i) {
        inv[p[i]-1] = i+1;
    }

    return inv;
}

void Permutation::print(std::ostream &os)
{
    int n = getNumElmts();
    
    for(int i = 1; i <= n; ++i) {
        os << getElement(i);
        if (i < n)
            os << ",";
    }
}
 