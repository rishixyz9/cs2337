#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

//g++ main.cpp -Wall -Wextra -Wuninitialized -pedantic-errors -Wconversion 

//1: 244 376 587 751 630
//2: 406 846 770 994 974
//3: 974 846 341 994 905 296 849 390 770 406 889
//4: 169 192 170 194 181
//5: 190 192 194 243 150 246 154 202 157 158 164 165 168 169 170 175 178 179 180 181 182 183 187

/* 
 * Rishabh Vemparala
 * rxv200022
 * CS 2337.02
 */

using namespace std;

int Hash(int size, int key){
    return key % size;
}

bool isPrime(int n){
    if (n <= 1){
        return false;
    }
    if (n <= 3){
        return true;
    }
    if (n%2 == 0 || n%3 == 0){
        return false;
    }
    for (int i=5; i*i<=n; i=i+6){
        if (n%i == 0 || n%(i+2) == 0){
           return false;
        }
    }
    return true;
}

int nextSize(int size){
    if (size <= 1)
        return 2;
    int newSize = size;
    bool found = false;
    while (!found) {
        newSize++;
        if (isPrime(newSize))
            found = true;
    }
    return newSize;
}

bool mapInsert(int map[], int size, int key){
    int i = 0;
    int probed = 0;
    int bucket = Hash(size, key);
    while(probed < size){
        if(!map[bucket] || key == 0){
            map[bucket] = key;
            return true;
        }
        i++;
        bucket = (Hash(size, key) + (i*i)) % size;
        probed++;
    }
    return false;

}

int *HashResize(int hashTable[], int currentSize) {
    int *newArray = new int[nextSize(currentSize*2)]{0};
    for(int i=0; i < currentSize; i++){
        mapInsert(newArray, nextSize(currentSize*2), hashTable[i]);
    }
    return newArray;
}

void print(int *map, int &size){
    for(int i=0; i < size; i++){
        if(map[i]){
            cout << map[i] <<" ";           
        }
        else{
            cout << "_ ";
        }

    }
    cout << endl;    
}

int main(){

    int size = 11;
    int items = 0;
    cout << "enter the size" << endl;
    cin >> items;
    cin.ignore();
    int *map = new int[size]{0};

    int i = 0;
    const double loadFactor = 0.5;
    int num;
    string line;
    cout << "enter the values" << endl;
    getline(cin, line);
    stringstream ss(line);
    while(i < items){
        ss >> num;
        double load = ((double) i)/size;
        if(load >= loadFactor){
            map = HashResize(map, size);
            size = nextSize(size*2);
            mapInsert(map, size, num);
        }
        else{
            mapInsert(map, size, num);
        }
        i++;
    }

    print(map, size);

    return 0;
}