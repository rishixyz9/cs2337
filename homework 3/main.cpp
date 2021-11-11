#include <iostream>
#include <string>
#include <cmath>
#include "Graph.h"

using namespace std;

//g++ main.cpp Graph.cpp -Wall -Wextra -Wuninitialized -pedantic-errors -Wconversion 

int main(){
	string fileName;
	cout << "What is the name of the file?: " << endl;
	cout << "> ";
	cin >> fileName;
	Graph newGraph;

	newGraph.createGraph(fileName);

	cout << (newGraph.isConnected() ?"connected":"not connected") << endl;

	return 0; 
}
