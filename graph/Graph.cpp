//
// Created by mgh-PC on 2017/7/11.
//

#include "Graph.h"



void Graph::buildGraph() {
    constructNodeIndex(nodes);
    constructEdgeIndex(edges);
    for(auto& edge: edges){
        Node* startNode = &nodes[nodePositionWithID[edge.getStartNodeID()]];
        Node* endNode = &nodes[nodePositionWithID[edge.getEndNodeID()]];
        startNode->addAdjacentNode(endNode);
        startNode->addAdjacentEdge(&edge);
        endNode->addAdjacentNode(startNode);
        endNode->addAdjacentEdge(&edge);
    }

}


void Graph::addNode(long long id, double x, double y){
    nodes.push_back(Node(id, x, y));
}


void Graph::addEdge(Edge edge) {
    edges.push_back(edge);
}

void Graph::addEdge(long long id, long long startNodeID, long long endNodeID, double edgeLength){
    edges.push_back(Edge(id, startNodeID, endNodeID, edgeLength));
}


void Graph::constructNodeIndex(vector<Node>& nodes){
    unordered_map<long long, size_t> mp;
    for(size_t i = 0; i < nodes.size(); i++){
        mp[nodes[i].getID()] = i;
    }
    nodePositionWithID = mp;
};


void Graph::constructEdgeIndex(vector<Edge>& edges){
    unordered_map<long long, size_t> mp;
    for(size_t i = 0; i < edges.size(); i++){
        mp[edges[i].()] = i;
    }
    edgePositionWithID = mp;
}


Edge* Graph::getEdgeByID(long long edgeID){
    return &edges[edgePositionWithID[edgeID]];
}

Node* Graph::getNodeByID(long long nodeID){
    return &nodes[nodePositionWithID[nodeID]];
}

double Graph::dijkstraDist(long long startNodeID, long long endNodeID){



}

