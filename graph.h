#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
struct graph {
    std::vector<std::vector<std::pair<double,int>*>> adjList;
    int numVertices = adjList.size();
    graph(std::vector<std::vector<std::pair<double,int>*>> adj) { this->adjList = adj; this->numVertices = adj.size();}
};
#endif // GRAPH_H
