#ifndef NODE_H
#define NODE_H

#include <iostream>

template<typename T>
class Node
{
private:
    T val;        //pointer to the object
    Node<T> *left;  //pointer to the left node
    Node<T> *right;  //pointer to the right node

public:
    Node(){left=nullptr, right=nullptr;}   //default constructor
    Node(T newVal){val=newVal, left=nullptr, right=nullptr;}   //overloaded constructor

    Node<T>* getLeft(){return left;}    //returns the next node pointer
    Node<T>* getRight(){return right;}    //returns the prev node pointer
    T getVal(){return val;}  //returns the value stored in the node

    void setLeft(Node<T>* newLeft){left=newLeft;}  //sets the left to newLeft
    void setRight(Node<T>* newRight){right=newRight;}  //sets the right to newRight
    void setVal(T newVal){val=newVal;}  //set the val to newVal
    Node<T> *min(); //returns the successor node

    bool operator< (Node<T>*);
    bool operator> (Node<T>*);
    bool operator== (Node<T>*);

    template<typename T1>
    friend std::ostream& operator<< (std::ostream&, Node<T1>*);
};

/*
 * min method returns the maximum of the left subtree
 */
template<typename T>
Node<T>* Node<T>::min(){
    Node<T> *cur = right;
    while(cur->getLeft()){
        cur = cur->getLeft();
    }
    return cur;
}

template<typename T>
bool Node<T>::operator< (Node<T>* rhs){
    if(val < rhs->val){
        return true;
    }
    return false;
}

template<typename T>
bool Node<T>::operator> (Node<T>* rhs){
    if(val > rhs->val){
        return true;
    }
    return false;
}

template<typename T>
bool Node<T>::operator== (Node<T>* rhs){
    if(val == rhs->val){
        return true;
    }
    return false;
}

//<name>, <high_score>, <initials>, <plays>, $<revenue><newline>
template<typename T>
std::ostream& operator<< (std::ostream& out, Node<T>* rhs){
    out << rhs->val;
    return out;
}



#endif