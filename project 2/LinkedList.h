#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <string>
#include <iostream>

template<class T>
class LinkedList
{
private:
    Node<T> *head;  //pointer to the head of the list
    Node<T> *tail;  //pointer to the tail of the list

public:
    LinkedList(){head=NULL, tail=NULL;} //default constructor of a LinkedList object
    LinkedList(Node<T>*);   //overloaded constructor which creates a LinkedList with a head/tail of a Node

    Node<T> *getHead(){return head;}    //returns the node at head
    Node<T> *getTail(){return tail;}    //returns the node at tail
    void setHead(Node<T>* newHead){head=newHead;}   //sets the node at head to newHead
    void setTail(Node<T>* newTail){tail=newTail;}   //sets the node at tail to newTail

    void append(Node<T>*); //adds a new node to the end of the LinkedList
    void sort(std::string); //sorts the LinkedList in asc/dec order depending on the parameter

    template<typename T1>
    friend std::ostream& operator<< (std::ostream&, LinkedList<T1>&);

};

/*
 * LinkedList object overloaded constructor
 * Takes in a generic Node object and creates a LinkedList with it as the head and tail
 */
template<class T>
LinkedList<T>::LinkedList(Node<T>* node){
    head=node; 
    tail=node;
}

/*
 * Sort method which sorts the LinkedList by mutating it
 * Takes in a string parameter to determine which way to sort the nodes
 * 2 cases of sorting: ascending and descending
 */
template<class T>
void LinkedList<T>::sort(std::string sortMethod){
    Node<T> *curr = head;
    if(sortMethod=="asc"){
        while(curr->getNext() != NULL){
            if(*curr->getData() > *curr->getNext()->getData()){
                Node<T> *nextNode = curr->getNext();
                nextNode->setPrev(curr->getPrev());
                curr->setPrev(nextNode);
                curr->setNext(nextNode->getNext());
                nextNode->setNext(curr);
                if(curr->getNext() != NULL){
                    curr->getNext()->setPrev(curr);
                }
                if(nextNode->getPrev() == NULL){
                    head = nextNode;
                }
                else{
                    nextNode->getPrev()->setNext(nextNode);
                }
                curr = head;
            }
            else{
                curr = curr->getNext();             
            }

        }
    }
    if(sortMethod=="des"){
        while(curr->getNext() != NULL){
            if(*curr->getData() < *curr->getNext()->getData()){
                Node<T> *nextNode = curr->getNext();
                nextNode->setPrev(curr->getPrev());
                curr->setPrev(nextNode);
                curr->setNext(nextNode->getNext());
                nextNode->setNext(curr);
                if(curr->getNext() != NULL){
                    curr->getNext()->setPrev(curr);
                }
                if(nextNode->getPrev() == NULL){
                    head = nextNode;
                }
                else{
                    nextNode->getPrev()->setNext(nextNode);
                }
                curr = head;
            }
            else{
                curr = curr->getNext();             
            }

        }
    }
    tail = curr;
}

/*
 * Append method
 * Adds the passed in newNode parameter as the tail of the list and 
 * sets the previous tail to the newNode prev and the previous tail next to newNode
 * If the list is empty, adds the newNode as the head and tail
 */
template<class T>
void LinkedList<T>::append(Node<T> *newNode){
    if(head == NULL){
        head = newNode;
        tail = newNode;
    }
    else{
        newNode->setPrev(tail);
        tail->setNext(newNode);
        tail = newNode;
    }
}

/*
 * Overloaded insertion operator
 * Allows for simple output of the LinkedList 
 * Starts at head and keeps on outputing the current node
 * until the node is null
 */
template<typename T1>
std::ostream& operator<< (std::ostream& out, LinkedList<T1>& list){
    Node<T1>*curr = list.getHead();
    if(curr == NULL){
        out << "list is empty";
    }
    else{
        while(curr != NULL){
            out << *curr->getData()<<'\n';
            curr = curr->getNext();
        }
    }
    return out;
}

#endif