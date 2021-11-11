//Rishabh Vemparala rxv200022
//Brian Pham bap200003

#ifndef BST_H
#define BST_H
#include "Node.h"


class BST
{
private:
    Node* root = nullptr;

public:
    BST(int x) {root = new Node(x);}
    ~BST();
    void deleteChildren(Node*);
    void add(Node*);
    bool search(int x);
    // void insert(Node*);
    Node* getRoot(){return root;}
    Node* deleteNode(int);
    void display();
};
#endif // BST_H
