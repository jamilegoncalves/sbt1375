#ifndef PERMUTATION_H
#define	PERMUTATION_H

class Permutation {

public:
    virtual int getNumElmts() = 0;

    /**
     * Returns the i-th element of the permutation.
     * The index i starts in 1. If i == 0, returns
     */
    virtual int getElement(int i) = 0;

    virtual void applyTransposition(int i, int j, int k) = 0;

    virtual Permutation *getInverse() = 0;

protected:
    static int *inverse(int *p, int n);
};


#endif	/* PERMUTATION_H */

