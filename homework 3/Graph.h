#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>

class Graph
{
private:
    std::vector<std::vector<int>> adjList;
    int curSize;
    int maxSize;

public:
    Graph(){curSize=0; maxSize=10;}
    Graph(int newSize){maxSize=newSize;}
    void createGraph(std::string fileName);
    bool dfs(int);
    void dfs(bool*, int);
    bool isEmpty(){return curSize==0;}
    bool isConnected();

};

#endif