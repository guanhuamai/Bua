//
// Created by mgh-PC on 2017/7/13.
//

#ifndef BUA_POINTONEDGE_H
#define BUA_POINTONEDGE_H

#include <string>

using namespace std;

class PointOnEdge{

private:
    long long id;
    double pos;
    long long edgeID;

public:
    long long getID() const ;
    double getPosition() const ;
    long long getEdgeID() const ;

    bool operator()(const PointOnEdge& p1, const PointOnEdge& p2) const {
        return p1.getID() < p2.getID();
    }

    PointOnEdge(long long movingObjectID, double position, long long adhereEdgeID):
            id(movingObjectID), pos(position), edgeID(adhereEdgeID){}

    string toString();
};


#endif //BUA_POINTONEDGE_H
