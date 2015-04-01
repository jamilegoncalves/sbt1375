#include <deque>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Permutation.h"
#include "PermutationArray.h"
#include "PermutationTree.h"
#include "Node.h"

using namespace std;

PermutationTree::PermutationTree(Permutation *p)
{
    build(p);
}

PermutationTree::PermutationTree() {
}

PermutationTree::PermutationTree(Node *root) {
    this->root = root;
}

void deleteSubtree(Node *root) {
    if (root == NULL)
        return;
    else
    {
        deleteSubtree(root->left);
        deleteSubtree(root->right);
        delete root;
    }
}

PermutationTree::~PermutationTree() {
    deleteSubtree(root);
}


int PermutationTree::getNumElmts() {
    return root->leavesInSubtree;
}

Permutation *PermutationTree::getInverse() {
    int n = getNumElmts();
    int *p = new int[n];
    for(int i=0; i<n; ++i) {
        p[i] = getElement(i+1);
    }
    int *inv = inverse(p, n);
    PermutationArray *pa = new PermutationArray(inv , n);
    PermutationTree *ret = new PermutationTree(pa);
    delete pa;
    delete inv;
    delete p;
    return ret;
}

bool find(Node *t, int i, deque<Node *> &path) {
    int n = t->leavesInSubtree;

    if (i <= n) {
        path.push_front(t);
    } else {
        return false;
    }

    if (n == 1)
        return true;

    if (i <= t->left->leavesInSubtree) {
        return find(t->left, i, path);
    } else {
        return find(t->right, i - t->left->leavesInSubtree, path);
    }
}

element_t PermutationTree::getElement(int i) {
    if (i > getNumElmts()) {
        return getNumElmts()+1;
    } else if (i <= 0) {
        return 0;
    } else {
        deque<Node *> path;
        find(root, i, path);
        Node *leaf = path.front();
        return leaf->gene;
    }
}

int PermutationTree::indexOf(element_t element) {
    Node *leaf = geneToLeaf[element];
    int idx = 1;
    Node *curr = leaf;
    while (curr->parent != NULL) {
        Node *parent = curr->parent;
        if (curr == parent->right && parent->left != NULL) {
            idx = idx + parent->left->leavesInSubtree;
        }
        curr = curr->parent;
    }
    return idx;
}

int ceilLog2(int n)
{
    if (n <= 0)
        return 1;
    int nbits = sizeof(n)*8;
    int k = 0, numOnes = 0;
    for (int i = 0; i < nbits; ++i)
    {
        int a0 = n & 1;
        if (a0 == 1)
        {
            ++numOnes;
            k = i;
        }
        n = n >> 1;
    }
    if (numOnes == 1)
    {
        return k;
    }
    else
    {
        return k+1;
    }
}


void recalculate(Node *t) {
    t->height = max(t->left->height, t->right->height) + 1;
    t->gene = max(t->left->gene, t->right->gene);
    t->leavesInSubtree = t->left->leavesInSubtree +
                         t->right->leavesInSubtree;
    t->left->parent = t;
    t->right->parent = t;
}

void PermutationTree::build(Permutation *p)
{
    int n = p->getNumElmts();
    Node **V = new Node*[n+1];
    Node **U = new Node*[n+1];

    geneToLeaf = new Node*[n+1];
 
    for(int i = 1; i <= n; ++i)
    {
        Node *leaf = new Node;
        leaf->parent = NULL;
        leaf->gene = p->getElement(i);
        leaf->left = NULL;
        leaf->right = NULL;
        leaf->height = 0;
        leaf->leavesInSubtree = 1;
        U[i] = leaf;
        geneToLeaf[leaf->gene] = leaf;
    }
    //U->print(cerr);

    int k = n;

    while(k>1)
    {
        for(int i = 1; i <= k/2; ++i)
        {
            Node *v = new Node;
            v->parent = NULL;
            v->left = U[2*i-1];
            v->right = U[2*i];
            recalculate(v);
            V[i] = v;
        }

        if(k%2 == 0)
        {
            swap(U, V);
        }
        else
        {
            Node* v = new Node;
            v->parent = NULL;
            v->left = V[k/2];
            v->right = U[k];
            recalculate(v);
            swap(U, V);
            U[k/2] = v;
        }

        k = k/2;
        //U->print(cerr);
    }

    root = U[1];
    delete U;
    delete V;
}

PermutationTree *PermutationTree::join(PermutationTree *t1, PermutationTree *t2)
{
    PermutationTree *newtree = new PermutationTree();
    newtree->root = join(t1->root, t2->root);
    t1->root = NULL;
    t2->root = NULL;
    return newtree;
}

Node *PermutationTree::join(Node *t1, Node *t2)
{
    if (t1 == NULL) {
        return t2;
    } else if (t2 == NULL) {
        return t1;
    }

    if( abs(t1->height - t2->height) <= 1 )
    {
        Node *t = new Node;
        t->parent = NULL;

        t->left = t1;
        t->right = t2;
        recalculate(t);
        return t;
    }
    else if( t1->height - t2->height == 2 )
    {
        if(t1->left->height >= t1->right->height)
        {
            Node *tprime = new Node; // tprime = t'
            tprime->parent = NULL;
            Node *t = new Node;
            t->parent = NULL;

            tprime->left = t1->right;
            tprime->right = t2;
            recalculate(tprime);
            t->left = t1->left;
            t->right = tprime;
            recalculate(t);
            delete t1;
            return t;
        }
        else
        {
            Node *tprimeprime = new Node; // tprimeprime = t"
            tprimeprime->parent = NULL;
            Node *tprime = new Node; // tprime = t'
            tprime->parent = NULL;
            Node *t = new Node;
            t->parent = NULL;

            tprime->left = t1->left;
            tprime->right = t1->right->left;
            recalculate(tprime);
            tprimeprime->left = t1->right->right;
            tprimeprime->right = t2;
            recalculate(tprimeprime);
            t->left = tprime;
            t->right = tprimeprime;
            recalculate(t);
            delete t1->right;
            delete t1;
            return t;
        }
    }
    else if( t1->height - t2->height == -2 )
    {
        if(t2->left->height <= t2->right->height)
        {
            Node *tprime = new Node; // tprime = t'
            tprime->parent = NULL;
            Node *t = new Node;
            t->parent = NULL;

            tprime->left = t1;
            tprime->right = t2->left;
            recalculate(tprime);
            t->left = tprime;
            t->right = t2->right;
            recalculate(t);
            delete t2;
            return t;
        }
        else
        {
            Node *tprimeprime = new Node; // tprimeprime = t"
            tprimeprime->parent = NULL;
            Node *tprime = new Node; // tprime = t'
            tprime->parent = NULL;
            Node *t = new Node;
            t->parent = NULL;

            tprime->left = t1;
            tprime->right = t2->left->left;
            recalculate(tprime);
            tprimeprime->left = t2->left->right;
            tprimeprime->right = t2->right;
            recalculate(tprimeprime);
            t->left = tprime;
            t->right = tprimeprime;
            recalculate(t);
            delete t2->left;
            delete t2;
            return t;
        }
    }
    else if ( t1->height - t2->height > 2 )
    {
        Node *t = join(t1->left, join(t1->right, t2));
        delete t1;
        return t;
    }
    else // ( t1->height - t2->height < -2 )
    {
        Node *t = join(join(t1, t2->left), t2->right);
        delete t2;
        return t;
    }
}

pair<Node *, Node *>
PermutationTree::split(Node* &root, int m)
{
    deque<Node *> path;
    find(root, m, path);

    Node *tr = path.front(); // tr <- v0
    Node *tl = NULL;

    path.pop_front(); // Removes v0 element

    Node *lastNode = tr;

    deque<Node *>::iterator _node;

    for (_node = path.begin(); _node != path.end(); ++_node)
    {
        if((*_node)->left->gene == lastNode->gene)
        {
            tr = join(tr, (*_node)->right);
        }
        if((*_node)->right->gene == lastNode->gene)
        {
            tl = join((*_node)->left, tl);
        }

        lastNode = (*_node); // lastNode is vi
    }

    // the nodes in the path will not be used anymore,
    // delete them
    for (_node = path.begin(); _node != path.end(); ++_node)
    {
        delete (*_node);
    }

    if (tl != NULL) {
        tl->parent = NULL;
    }
    if (tr != NULL) {
        tr->parent = NULL;
    }
    pair<Node *, Node*> ret(tl,tr);
    root = NULL;
    return ret;
}

int PermutationTree::query(int i, int j)
{
    Node *t1, *t2, *t3;
    /*
     * t1 = trees.first = [a1, ..., ai]
     * trees.second = [ai+1, ..., an]
     */
    std::pair<Node*,Node*> trees = split(root, i+1);
    t1 = trees.first;

    /*
     * t2 = treesPrime.first = [ai+1, ..., aj]
     * t3 = treesPrime.second = [aj+1, ..., an]
     */
    std::pair<Node*,Node*> trees2 = split(trees.second, j-i+2);
    trees.second = NULL;
    t2 = trees2.first;
    t3 = trees2.second;

    int pk = t2->gene;
    int k = findGene(t2, pk) + i;

    root = join(t1, join(t2, t3));

    return k;
}

int PermutationTree::findGene(Node *root, int gene) {
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    if (root->left != NULL && root->left->gene == gene) {
        int i = findGene(root->left, gene);
        return i;
    } else {
        int i = findGene(root->right, gene);
        if (root->left == NULL) {
            return i;
        } else {
            return root->left->leavesInSubtree + i;
        }
    }
}

void PermutationTree::applyTransposition(int i, int j, int k)
{
    Node *t1, *t2, *t3, *t4;
    /*
     * trees.first = [a1, ..., ai-1]
     * trees.second = [ai, ..., an]
     */
    std::pair<Node*,Node*> trees = split(root, i);
    t1 = trees.first;

    /*
     * trees2.first = [ai, ..., aj-1]
     * trees2.second = [aj, ..., an]
     */
    std::pair<Node*,Node*> trees2 = split(trees.second, j-i+1);
    t2 = trees2.first;

    /*
     * t3 = trees3.first = [aj, ..., ak-1]
     * t4 = trees3.second = [ak, ..., an]
     */
    std::pair<Node*,Node*> trees3 = split(trees2.second, k-j+1);
    t3 = trees3.first;
    t4 = trees3.second;

    this->root = join(join(join(t1, t3), t2), t4);
}

ostream &PermutationTree::prettyPrint(ostream &os)
{
    prettyPrint(os, root, "");
    return os;
}

void PermutationTree::prettyPrint(ostream &os, Node *root,
        string spacer)
{
    if (root == NULL) {
        os << "NULL" << endl;
        return;
    }
    os <<           root->gene << endl;
    if (root->left != NULL || root->right != NULL) {
        os << spacer << "├─ ";
        prettyPrint(os, root->left, spacer + "│  ");
        os << spacer << "└─ ";
        prettyPrint(os, root->right, spacer + "   ");
    }
}
