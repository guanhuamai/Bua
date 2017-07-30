//
// Created by mgh-PC on 2017/7/11.
//

#ifndef BUA_EDGE_H
#define BUA_EDGE_H


#include <string>

using namespace std;

class Edge {
protected:
    long long id;
    long long startNodeID;
    long long endNodeID;
    double edgeLength;

public:

    Edge(long long id, long long startNodeID, long long endNodeID, double edgeLength);
    virtual string toString();
    long long getID() const;
    long long  getStartNodeID() const ;
    long long getEndNodeID() const ;
    double getEdgeLength() const ;
    long long getOppositeNodeID(long long nodeID) const ;

};


#endif //BUA_EDGE_H
