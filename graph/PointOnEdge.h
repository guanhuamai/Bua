//
// Created by mgh-PC on 2017/7/13.
//

#ifndef BUA_POINTONEDGE_H
#define BUA_POINTONEDGE_H


class PointOnEdge{

private:
    long long id;
    double pos;
    long long edgeID;

public:
    long long getID();
    double getPosition();
    long long getEdgeID();

};


#endif //BUA_POINTONEDGE_H
