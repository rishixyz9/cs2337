#include "Graph.h"
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <stack>

void Graph::createGraph(std::string fileName){
    std::ifstream fileInput(fileName);
    int temp;
    std::string line;
    fileInput >> temp;
    curSize = temp;
    fileInput.ignore();
    std::vector<std::vector<int>> resized(curSize);
    adjList = resized;
    std::vector<int> rowVector;
    while(std::getline(fileInput, line)){
        std::stringstream ss(line);
        int index;
        int num;
        ss >> index;
        while(ss >> num){
            rowVector.push_back(num);
        }
        adjList[index-1] = rowVector;
        rowVector.clear();
    }
    for(std::vector<int> x: adjList){
        for(int y: x){
            std::cout << y << " ";
        }
        std::cout << std::endl;
    }
    fileInput.close();
}

bool Graph::dfs(int start){
    bool *visited = new bool[curSize]{false};
    dfs(visited, start);
    if(curSize==1){
        return false;
    }
    for(int i=0; i < curSize; i++){
        if(!visited[i]){
            delete(visited);
            return false;
        }
    }
    delete(visited);
    return true;
}

void Graph::dfs(bool* visited,int start){
    visited[start-1] = true;
    for(int y: adjList[start-1]){
        if(!visited[y-1]){
            dfs(visited, y);
        }
    }
}

bool Graph::isConnected(){
    for(int x=1; x <= curSize; x++){
        if(!dfs(x)){
            return false;
        }
    }
    return true;
}