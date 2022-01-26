#include <iostream>
using namespace std;
//g++ main.cpp -Wall -Wextra -Wuninitialized -pedantic-errors -Wconversion 

int partition(int theArray[], int first, int last,int &counter) {
    int pivotIndex = sortFirstMiddleLast(theArray, first, last);
    std::swap(theArray[pivotIndex], theArray[last - 1]);
    pivotIndex = last - 1;
    ItemType pivot = theArray[pivotIndex];
    int indexFromLeft = first + 1;
    int indexFromRight = last - 2;

    bool done = false;
    while (!done) {
        while (theArray[indexFromLeft] < pivot) {
          counter++;
          indexFromLeft = indexFromLeft + 1;
        }
        while (theArray[indexFromRight] > pivot) {
          counter++;
          indexFromRight = indexFromRight - 1;
        }

        if (indexFromLeft < indexFromRight) {
            std::swap(theArray[indexFromLeft], theArray[indexFromRight]);
            indexFromLeft = indexFromLeft + 1;
            indexFromRight = indexFromRight - 1;
        }
        else {
            done = true;
        }
    }
    std::swap(theArray[pivotIndex], theArray[indexFromLeft]);
    pivotIndex = indexFromLeft;
    return pivotIndex;
}

int quicksort(int theArray[], int first, int last) {
    int result = 0;
    int counter = 0;
    if (last - first + 1 < MIN_SIZE) {
        result = insertionSort(theArray, first, last);
    }
    else {
        int pivotIndex = partition(theArray, first, last,counter);
         result += quicksort(theArray, first, pivotIndex - 1);
         result += quicksort(theArray, pivotIndex + 1, last);
         result += counter;
    }
    return result; //return final count
}

int main()
{
   int arr1[5000];
   int arr2[5000];
   int arr3[5000];
   int arr4[5000];
   for(int i=0;i<5000;i++){
      arr1[i]=rand()%5000;
      arr2[i]=rand()%5000;
      arr3[i]=rand()%5000;
      arr4[i]=rand()%5000;
   }

   int comps=0;
   int swaps=0;

   //bubble sort
   for(int i = 0; i<5000; i++) {
      for(int j = i+1; j<5000; j++)
      {
         if(arr1[j] < arr1[i]) {
            int temp = arr1[i];
            arr1[i] = arr1[j];
            arr1[j] = temp;
            swaps++;
         }
         comps++;
      }
   }
   cout << "Bubble Sort:" << endl;
   cout << "comparisons: " << comps << " swaps: " << swaps << endl;

   //selection sort
   comps = 0;
   swaps = 0;
   int minIndex, tmp;    
   for (int i = 0; i < 4999; i++) {
      minIndex = i;
      for (int j = i + 1; j < 5000; j++){
         if (arr2[j] < arr2[minIndex]){
            minIndex = j;                 
         }
         comps++;         
      }
      if (minIndex != i) {
         tmp = arr2[i];
         arr2[i] = arr2[minIndex];
         arr2[minIndex] = tmp;
         swaps++;
      }
   }
   cout << "Selection Sort:" << endl;
   cout << "comparisons: " << comps << " swaps: " << swaps << endl;

   //insertion sort
   comps = 0;
   swaps = 0;
   int key;
   for(int i = 1; i<5000; i++) {
      key = arr3[i];//take value
      int j = i;
      while(j > 0 && arr3[j-1]>key) {
         arr3[j] = arr3[j-1];
         j--;
         comps++;
         swaps++;
      }
      arr3[j] = key;   //insert in right place
   }

   cout << "Insertion Sort:" << endl;
   cout << "comparisons: " << comps << " swaps: " << swaps << endl;

   //quick sort

   return 0;
}