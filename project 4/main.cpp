#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Graph.h"

//g++ main.cpp Graph.cpp -Wall -Wextra -Wuninitialized -pedantic-errors -Wconversion 

/* 
 * Rishabh Vemparala
 * rxv200022
 * CS 2337.02
 */

using namespace std;

//Function prototypes of functions defined below main
int calculateRoute(Graph&, vector<string>);
void sortResult(Graph&, vector<vector<string>>&);
void readRoutes(Graph&, string&);


int main(){
    string fileName;
    Graph newGraph;
    cout << "What is the name of the first file?: " << endl;
    cout << "> ";
    cin >> fileName;
    newGraph.createGraph(fileName); //reads the file containing the graph and constructs it into newGraph
    cout << "What is the name of the second file?: " << endl;
    cout << "> ";
    cin >> fileName;
    readRoutes(newGraph, fileName); //reads the file containing the driver paths and prints out the results

    return 0;
} 

/*
 * readRoutes method reads the file containing the driver routes
 * takes a Graph parameter and a string filename parameter
 * uses the Graph object to verify if the paths in the file
 * are valid and outputs the results to the console
 */
void readRoutes(Graph& locations, string& fileName){
    ifstream fileInput(fileName);
    //if the file is valid then the following code will execute
    if(fileInput.is_open()){
        cout << "routes file successfully opened" << endl;
        vector<vector<string>> driverVector;
        while(!fileInput.eof() && fileInput.good()){
            string line;
            getline(fileInput, line);
            stringstream ss(line);
            string temp;
            vector<string> path;
            while(ss >> temp){
                path.push_back(temp);
            }
            driverVector.push_back(path);
            path.clear();
        }

        //sorts the results
        sortResult(locations, driverVector);
        
        //outputs the results
        for(vector<string> x: driverVector){
            if(calculateRoute(locations, x)>0)
                cout << x[0] << "\t" << calculateRoute(locations, x) << "\t" << "valid" << endl;
            else
                cout << x[0] << "\t" << 0 << "\t" << "invalid" << endl;
        }
    }
    fileInput.close();
}

/*
 * sortResults method uses a modified bubblesort to sort the results
 * takes a Graph parameter and a vector of string vectors of the results
 * uses the Graph object to help compare each driver that was in the file
 * the path weights are first sorted by ascending order
 * if path weights are the same then they are sorted by alphabetical order
 */
void sortResult(Graph& locations, vector<vector<string>> &driverVector){

    //first block sorts the results by ascending weight order
    bool swap = true;
    while(swap)
    {
        swap = false;
        for (int i = 0; i < (int) driverVector.size()-1; i++)
        {
            if (calculateRoute(locations, driverVector[i])>calculateRoute(locations, driverVector[i+1]))
            {
                vector<string> hold = driverVector[i];
                driverVector[i] = driverVector[i+1];
                driverVector[i+1] = hold;
                swap = true;
            }
        }
    }

    //second block sorts the results which have the same weights by ascending alphabetical order
    for (int i = 0; i < (int) driverVector.size()-1; i++)
    {
        if (calculateRoute(locations, driverVector[i])==calculateRoute(locations, driverVector[i+1]))
        {
            if(driverVector[i][0] < driverVector[i+1][0]){
                break;
            }
            vector<string> hold = driverVector[i];
            driverVector[i] = driverVector[i+1];
            driverVector[i+1] = hold;
            swap = true;
        }
    }
} 


/*
 * calculateRoute method calculates the weight of a path
 * if the path is invalid then 0 is returned
 * otherwise the wieght in integer form is returned
 * takes in a Graph object and vector of paths which was produced
 * by the readRoutes method
 */
int calculateRoute(Graph& locations, vector<string> path){
    int total=0;
    for(int i=1; i < (int) path.size()-1; i++){
        if(locations.traverse(path[i], path[i+1]) >= 0){
            total+=locations.traverse(path[i], path[i+1]);
        }
        else{
            return 0;
        }
    }
    return total;
}    