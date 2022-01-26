#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>

class Graph
{
private:
    //both vectors are used as the adjacency lists/matrix
    std::vector<std::vector<std::string>> edges; //contains the edges who belong to the corresponding vertex at the same index in the vertices variable
    std::vector<std::string> vertices; //vector of strings which contain the vertices
    int size; //number of vertices in the graph

public:
    Graph(){size=0;} //default constructor of a Graph object
    Graph(int newSize){size=newSize;} //overloaded constructor which creates a Graph object with size of newSize
    void createGraph(std::string fileName); //reads a file and fills the adjacency lists/matrix
    bool getSize(){return size;} //returns the size of the graph
    int traverse(std::string, std::string); //traverses from one point to the next
    int getIndex(std::string); //gets the index of a vertex
    void insertVertex(std::string);
    void insertEdge(std::string, std::string);
    void deleteEdge(std::string); //deletes an edge from all vertices
    void deleteVertex(std::string); //deletes a vertex and from everywhere it is an edge

};

#endif