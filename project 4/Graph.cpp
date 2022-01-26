#include "Graph.h"
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <queue>

/*
 * getIndex is a helper method which returns the index of a vertex
 * takes a String parameter
 * if the vertex is found it returns the index
 * otherwise returns -1
 */
int Graph::getIndex(std::string vertex){
    for(int i=0; i < (int) vertices.size(); i++){
        if(vertices[i]==vertex){
            return i;
        }
    }
    return -1;
}

/*
 * readRoutes method reads the file containing the Graph data
 * takes a string filename parameter
 * stores all the vertices in the vertices variable
 * stores the edges is the edges variable
 */
void Graph::createGraph(std::string fileName){
    std::ifstream fileInput(fileName);
    std::string temp;
    std::string line;
    std::vector<std::string> rowVector;
    while(std::getline(fileInput, line)){
        std::stringstream ss(line);
        std::string edge;
        ss >> edge;
        vertices.push_back(edge);
        while(ss >> edge){
            rowVector.push_back(edge);
        }
        edges.push_back(rowVector);
        rowVector.clear();
    }
    fileInput.close();
}

/*
 * traverse method travels from one point to the next
 * takes 2 string parameters
 * travels from start to end
 * if it is possible to go directly from start to end 
 * the weight is returned
 * otherwise -1 is returned
 */
int Graph::traverse(std::string start, std::string end){
    int total=0;
    int startIndex = getIndex(start);
    if(startIndex < 0){
        // std::cout << start << std::endl;
        return -1;
    }
    for(int i=0; i < (int) edges[startIndex].size(); i++){
        std::string edge = edges[startIndex][i].substr(0, (int)edges[startIndex][i].find(','));
        if(edge==end){
            total+=stoi(edges[startIndex][i].substr(edge.length()+1, edges[startIndex][i].length() - edge.length()));
            return total;
        }
    }
    return -1;
}

/*
 * insertVertex method inserts a vertex into the graph
 * takes a string parameter
 * modifies the vertices variable
 */
void Graph::insertVertex(std::string vertex){
    vertices.push_back(vertex);
}

/*
 * insertEdge method inserts a vertex's edges into the graph
 * takes 2 string parameters
 * inserts the edges at the index of the vertex variable
 * modifies the edges and vertices variable
 */
void Graph::insertEdge(std::string vertex, std::string line){
    std::stringstream ss(line);
    std::vector<std::string> rowVector;
    std::string edge;
    while(ss >> edge){
        rowVector.push_back(edge);
    }
    edges.insert(edges.begin() + getIndex(vertex), rowVector);
}

/*
 * deleteEdge method deletes all instances of an edge from the graph
 * takes a string parameter
 * modifies the edges variable
 */
void Graph::deleteEdge(std::string point){
    for(int i=0; i < (int)edges.size(); i++){
        for(int j=0; j < (int)edges[i].size(); j++){
            if(edges[i][j].find(point) != std::string::npos){
                std::cout << edges[i][j] << std::endl;
                edges[i].erase(edges[i].begin()+j);
            }           
        }
    }
}

/*
 * deleteEdge method deletes all instances of a vertex from the graph
 * takes a string parameter
 * utilizes deleteEdge method to delete all instances of a vertex from 
 * edges since it is no longer a valid point of travel 
 * modifies the vertices and edges variable
 */
void Graph::deleteVertex(std::string point){
    for(int i=0; i < (int) vertices.size(); i++){
        if(vertices[i]==point){
            vertices.erase(vertices.begin()+i);
            edges.erase(edges.begin()+i);
        }
    }
    deleteEdge(point);
}