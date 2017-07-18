//
// Created by mgh-PC on 2017/7/11.
//

#include "Node.h"



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
