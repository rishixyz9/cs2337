#ifndef VECTORTEMPLATE_H
#define VECTORTEMPLATE_H

#include <iostream>
#include <vector>

template<typename T>
class VectorTemplate
{
private:
    std::vector<T> vectorVar;

public:
    void setVector(T);
    std::vector<T> getVector(){return vectorVar;}
    VectorTemplate(){;}
    VectorTemplate(std::vector<T>&);
    void InsertionSort();
    bool BinarySearch(T);


};

template<typename T>
void VectorTemplate<T>::setVector(T newNode){
    vectorVar.push_back(newNode);
}

template<typename T>
VectorTemplate<T>::VectorTemplate(std::vector<T>& copyVector){
    vectorVar = copyVector;
}

template<typename T>
void VectorTemplate<T>::InsertionSort(){
    for(int i=1; i < (int)vectorVar.size(); ++i){
        int sortedSize = i;
        while(sortedSize > 0 && vectorVar[sortedSize-1] > vectorVar[sortedSize]){
            T temp = vectorVar[sortedSize];
            vectorVar[sortedSize] = vectorVar[sortedSize-1];
            vectorVar[sortedSize-1] = temp;
            sortedSize--;
        }
    }
}

template<typename T>
bool VectorTemplate<T>::BinarySearch(T key) {
   int mid;
   int low;
   int high;
   
   low = 0;
   high = vectorVar.size() - 1;
   
   while (high >= low) {
      mid = (high + low) / 2;
      if (vectorVar[mid] < key) {
         low = mid + 1;
      }
      else if (vectorVar[mid] > key) {
         high = mid - 1;
      }
      else {
         return true;
      }
   }
   
   return false; // not found
}




#endif