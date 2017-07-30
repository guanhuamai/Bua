//
// Created by mgh-PC on 2017/7/11.
//

#include "Edge.h"


string Edge::toString(){

    string s;
    s += "edge id: " + to_string(id)
         + "start node: " + to_string(startNodeID)
         + "end node: " + to_string(endNodeID)
         + "edge length: " + to_string(edgeLength)
         + "\n";
    return s;

}

long long Edge::getID() const{
    return id;
}

Edge::Edge(long long id, long long startNodeID, long long endNodeID, double edgeLength){
    this->id = id;
    this->startNodeID = startNodeID;
    this->endNodeID = endNodeID;
    this->edgeLength = edgeLength;
}

long long Edge::getStartNodeID() const {
    return startNodeID;
}


long long Edge::getEndNodeID() const {
    return endNodeID;
}

double Edge::getEdgeLength() const {
    return edgeLength;
}

long long Edge::getOppositeNodeID(long long nodeID) const {
    if (nodeID == startNodeID){
        return endNodeID;
    } else if (nodeID == endNodeID){
        return startNodeID;
    } else {
        return -1;
    }
}
