//
// Created by mgh-PC on 2017/7/11.
//

#include "Node.h"
#include "../utility/Utility.h"
#include <iostream>
using namespace std;


Node::Node(long long id, double x, double y){
    adjacentEdges.clear();
    adjacentNodes.clear();
    this->id = id;
    this->x = x;
    this->y = y;
}

long long Node::getID() { return id;}
double Node::getX() { return x;}
double Node::getY() { return y;}

size_t Node::addAdjacentEdge(Edge* edge){
    adjacentEdges.push_back(edge);
    return adjacentEdges.size();
}

size_t Node::addAdjacentNode(Node *node) {
    adjacentNodes.push_back(node);
    return adjacentNodes.size();
}


vector<Node*> Node::getAdjacentNodes(){
    return adjacentNodes;
}
vector<Edge*> Node::getAdjacentEdges(){
    return adjacentEdges;
}


vector<Node*> Node::nodeFromDiskFile(const string nodeFile){
    vector<Node*> res;
    vector<string> nodesStr = Utility::readLines(nodeFile);
    for (size_t i = 1; i < nodesStr.size(); i++){
        vector<string> splitInfo = Utility::split(nodesStr[i], '\t');
        long long nodeID = Utility::my_stoi(splitInfo[0]);
        double nodeX = Utility::my_stof(splitInfo[1]);
        double nodeY = Utility::my_stof(splitInfo[2]);
        res.push_back(new Node(nodeID, nodeX, nodeY));
    }
    cout << "input nodes: " << res.size() << endl;
    return  res;
}
