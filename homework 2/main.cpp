#include <iostream>
#include <string>
#include <cmath>
#include "VectorTemplate.h"

using namespace std;

//g++ main.cpp -Wall -Wextra -Wuninitialized -pedantic-errors -Wconversion 

int main(){

	VectorTemplate<int> intVector;
	intVector.setVector(3);
	intVector.setVector(1);
	intVector.setVector(2);
	intVector.setVector(0);
	intVector.setVector(7);
	intVector.setVector(11);
	intVector.setVector(4);
	intVector.setVector(8);

	intVector.InsertionSort();

	cout << intVector.BinarySearch(5) << endl;
	cout << intVector.BinarySearch(8) << endl;

	for(int i=0; i < (int)intVector.getVector().size(); i++){
		cout << intVector.getVector()[i] << " ";
	}
	cout << endl << endl;

	VectorTemplate<double> doubleVector;
	doubleVector.setVector(9.1);
	doubleVector.setVector(3.123);
	doubleVector.setVector(2.34);
	doubleVector.setVector(3.14);
	doubleVector.setVector(7.34);
	doubleVector.setVector(0.12);
	doubleVector.setVector(4.2);
	doubleVector.setVector(6.9);

	doubleVector.InsertionSort();

	cout << doubleVector.BinarySearch(5.0) << endl;
	cout << doubleVector.BinarySearch(0.12) << endl;

	for(int i=0; i < (int)doubleVector.getVector().size(); i++){
		cout << doubleVector.getVector()[i] << " ";
	}
	cout << endl << endl;


	VectorTemplate<string> stringVector;
	stringVector.setVector("hi");
	stringVector.setVector("bye");
	stringVector.setVector("a");
	stringVector.setVector("frog");
	stringVector.setVector("jumped");
	stringVector.setVector("on");
	stringVector.setVector("a");
	stringVector.setVector("6.1");

	stringVector.InsertionSort();

	cout << stringVector.BinarySearch("no") << endl;
	cout << stringVector.BinarySearch("frog") << endl;

	for(int i=0; i < (int)stringVector.getVector().size(); i++){
		cout << stringVector.getVector()[i] << " ";
	}
	cout << endl << endl;

	return 0; 
}
