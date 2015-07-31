#ifndef PERMUTATION_H
#define	PERMUTATION_H
#include <iostream>

typedef int element_t;

class Permutation {

public:
    virtual int getNumElmts() = 0;
    virtual ~Permutation();

    /**
     * Returns the i-th element of the permutation.
     * The index i starts in 1. If i == 0, returns
     * 0. If i == n+1, returns n+1.
     */
    virtual element_t getElement(int i) = 0;

    virtual void applyTransposition(int i, int j, int k) = 0;

    virtual Permutation *getInverse() = 0;

    virtual void print(std::ostream &os);

protected:
    static int *inverse(int *p, int n);
};


#endif	/* PERMUTATION_H */

