#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include <string>
#include <iostream>
#include <vector>

template<class T>
class Tree
{
private:
    Node<T> *root;  //pointer to the root of the list

public:
    Tree(){root=NULL;} //default constructor of a Tree object
    Tree(Node<T>* newNode){root=newNode;}   //overloaded constructor which creates a Tree with a head/tail of a Node
    Node<T>* getTree(){return root;}    //returns the whole tree
    void append(Node<T>*); //add a node to the tree
    void append(Node<T>*, Node<T>*); //recursive helper for add
    std::vector<Node<T>*> search(Node<T>*); //search a node to the tree returns similar or equal nodes
    void search(std::vector<Node<T>*>&, Node<T>*cur, Node<T>*key); //recursive helper for search
    Node<T>* removeNode(Node<T>*); //remove a node to the tree and return the removed node
    Node<T>* removeNode(Node<T>*, Node<T>*); //recursive helper for remove
    Node<T>* getPrev(Node<T>*); //returns the parent of a node
    Node<T>* getPrev(Node<T>*, Node<T>*); //recursive helper for getPrev

};

template<typename T>
void Tree<T>::append(Node<T> *newNode){
    if(root == NULL){
        root = newNode;
        return;
    }
    else{
        append(root, newNode);
    }
}

template<typename T>
void Tree<T>::append(Node<T> *cur, Node<T> *node){
    //moves left the node is less than the current node
    if(*cur > node){
        if(!(cur->getLeft())){
            cur->setLeft(node);
        }
        else{
            append(cur->getLeft(), node);
        }
    }
    //moves right the node is greater than the current node
    else{
        if(!(cur->getRight())){
            cur->setRight(node);
        }
        else{
            append(cur->getRight(), node);
        }
    }
}



template<typename T>
std::vector<Node<T>*> Tree<T>::search(Node<T>*key){
    std::vector<Node<T>*> nodeQueue;
    search(nodeQueue, root, key);
    return nodeQueue;   
}

template<typename T>
void Tree<T>::search(std::vector<Node<T>*> &nodeQueue, Node<T>*cur, Node<T>*key){
    if (cur != nullptr){
        search(nodeQueue, cur->getLeft(), key);
        if(*cur == key){
            nodeQueue.push_back(cur);
        }
        search(nodeQueue, cur->getRight(), key);  
    }  
}


template<typename T>
Node<T>* Tree<T>::removeNode(Node<T>* key){
    std::vector<Node<T>*> searchResult = search(key);
    if(searchResult.size()==0){
        return NULL;
    }
    return removeNode(getPrev(searchResult[0]), searchResult[0]);
}

template<typename T>
Node<T>* Tree<T>::removeNode(Node<T>* parent, Node<T>* key){
    if(!key){
        return nullptr;
    }
    else if(key==root && (!(key->getLeft() || key->getRight()) || (!key->getLeft() != !key->getRight()))){
        if (key->getLeft() != nullptr)
            root = key->getLeft();
        else
            root = key->getRight();       
    }

    //0 child
    else if(!(key->getLeft() || key->getRight())){
        if(*parent > key){ 
            parent->setLeft(nullptr);
        }
        else{
            parent->setRight(nullptr);           
        }
    }
    
    //2 child
    else if(key->getLeft() && key->getRight()){
        Node<T> *suc = key->min();
        Node<T> *hold = new Node<T>(key->getVal());
        key->setVal(suc->getVal());
        removeNode(getPrev(suc), suc);
        return hold;
    }
    //1 child
    else{
        if(*parent > key){
            if(key->getLeft()){
                parent->setLeft(key->getLeft());
                key->setLeft(NULL);
            }
            else{
                parent->setLeft(key->getRight());
                key->setRight(NULL);
            } 
        }
        else{
            if(key->getLeft()){
                parent->setRight(key->getLeft());
                key->setLeft(NULL);
            }
            else{
                parent->setRight(key->getRight());
                key->setRight(NULL);
            }
        }

    }
    return key;
}

template<typename T>
Node<T>* Tree<T>::getPrev(Node<T> *key){
    return getPrev(root, key);
}

template<typename T>
Node<T>* Tree<T>::getPrev(Node<T> *root, Node<T> *key){
    //node is root and has no parents
    if (root == NULL){
        return NULL;   
    }
    //node has a child that equals the key
    else if ((root->getLeft() == key) || (root->getRight() == key)){
        return root;    
    }
    //node is greater than the key
    else if(*key < root){
        return getPrev(root->getLeft(), key);       
    }
    //node is less than the key
    return getPrev(root->getRight(), key);

}

#endif