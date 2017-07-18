//
// Created by mgh-PC on 2017/7/11.
//

#ifndef BUA_NODE_H
#define BUA_NODE_H

#include <cstdlib>
#include <vector>
#include "Edge.h"

using namespace std;

class Node{
private:
    long long id;

    double x; // x coordinates
    double y; // y coordinates

    vector<Edge*> adjacentEdges; // init to be null
    vector<Node*> adjacentNodes; // init to be null

public:
    Node(long long id, double x, double y);
    long long getID();
    double getX();
    double getY();
    size_t addAdjacentEdge(Edge* edge);
    size_t addAdjacentNode(Node* node);

};


#endif //BUA_NODE_H
