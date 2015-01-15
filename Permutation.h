#ifndef PERMUTATION_H
#define	PERMUTATION_H
#include <iostream>

class Permutation {

public:
    virtual int getNumElmts() = 0;
    virtual ~Permutation();

    /**
     * Returns the i-th element of the permutation.
     * The index i starts in 1. If i == 0, returns
     */
    virtual int getElement(int i) = 0;

    virtual void applyTransposition(int i, int j, int k) = 0;

    virtual Permutation *getInverse() = 0;

    virtual void print(std::ostream &os);

protected:
    static int *inverse(int *p, int n);
};


#endif	/* PERMUTATION_H */

