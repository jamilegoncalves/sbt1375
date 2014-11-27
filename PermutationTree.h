#ifndef PERMUTATIONTREE_H
#define	PERMUTATIONTREE_H
#include <iostream>
#include <utility>
#include "Node.h"

class PermutationTree : public Permutation {

private:
    Node *root;

public:
    PermutationTree(Permutation *p);
    ~PermutationTree();
    Permutation *getInverse();

    /**
     * Joins two permutation trees. This method creates a new
     * permutation tree and empties the originals.
     * @param t1 - left permutation tree
     * @param t2 - right permutation tree
     * @return the union of the two trees
     */
    static PermutationTree *join(PermutationTree *t1, PermutationTree *t2);


    void applyTransposition(int i, int j, int k);
    int query(int i, int j);

    int getNumElmts();
    int getElement(int i);
    
    std::ostream &prettyPrint(std::ostream &os);
private:
    PermutationTree();
    PermutationTree(Node *root);

    void build(Permutation *p);
    
    static Node *join(Node *t1, Node *t2);
 
    /**
     * Splits this permutation tree into two. This method creates two new
     * permutation trees and empties the original.
     * @param m - where to split
     * @return a pair of root nodes
     */
    static std::pair<Node *, Node *> split(Node* &root, int m);

    static int findGene(Node *root, int gene);
    
    void prettyPrint(std::ostream &os, Node *root, std::string spacer);
};


#endif	/* PERMUTATIONTREE_H */



