#ifndef NODE_H
#define NODE_H

#include <string>
#include "Driver.h"

template<class T>
class Node
{
private:
    T *data;        //pointer to the object
    Node<T> *next;  //pointer to the next node
    Node<T> *prev;  //pointer to the previous object

public:
    Node(){next=NULL, prev=NULL;}   //default constructor
    Node(T&);   //overloaded constructor

    Node<T>* getNext(){return next;}    //returns the next node pointer
    Node<T>* getPrev(){return prev;}    //returns the prev node pointer
    T* getData(){return data;}  //returns the data stored in the node

    void setNext(Node* newNext){next=newNext;}  //sets the next pointer to newNext
    void setPrev(Node* newPrev){prev=newPrev;}  //sets the prev pointer to newPrev
    void setData(T&);

};


/*
 * Node object overloaded constructor
 * Takes in a generic object and creates a node with it as the data attribute
 */
template<class T>
Node<T>::Node(T& obj){
    data = new T(obj);
    next = NULL;
    prev = NULL;
}

/*
 * Node object mutator
 * Takes in a generic object and sets the node's data attribute to the passed in object
 */
template<class T>
void Node<T>::setData(T &newObj){
    data = newObj;
}


#endif