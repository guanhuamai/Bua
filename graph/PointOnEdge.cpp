//
// Created by mgh-PC on 2017/7/13.
//

#include "PointOnEdge.h"


long long PointOnEdge::getID() const {
    return id;
}

double PointOnEdge::getPosition() const {
    return pos;
}

long long PointOnEdge::getEdgeID() const {
    return edgeID;
}


string PointOnEdge:: toString(){
    string s;
    s += "id: " + to_string(id) + "edge id: " + to_string(edgeID) + " position: " + to_string(pos) + "\n";
    return s;
}
