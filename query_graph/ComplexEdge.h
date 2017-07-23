//
// Created by mgh-PC on 2017/7/13.
//

#ifndef BUA_COMPLEXEDGE_H
#define BUA_COMPLEXEDGE_H

#include "../graph/Edge.h"
#include "../graph/PointOnEdge.h"
#include "../graph/Graph.h"
#include "DistEdge.h"

using namespace std;

class ComplexEdge: public Edge {
    Graph* graph;
    vector<QueryEdge> queryEdges;
    vector<vector<DistEdge>> distEdges;
    vector<PointOnEdge> movingObjectsOnEdge; // moving objects adheres on the edge, can be empty
    vector<PointOnEdge> landmarksOnEdge;


    vector<DistEdge> splitByDist(PointOnEdge landmark);
    void splitByDist(vector<PointOnEdge> landmarks);

    void aggregateDistEdges();
public:
    ComplexEdge(long long int id, long long int startNodeID, long long int endNodeID, double edgeLength);

    void splitByAggregateValue(vector<PointOnEdge> landmarks);

    double calculateAggregateWithDistEdges(double pos);

//    vector<QueryEdgePointer> queryEdgePointers();
    vector<QueryEdge>& getQueryEdges();

    vector<PointOnEdge> getLandmarks();
    vector<PointOnEdge> getMovingObjects();

    QueryEdge* getQueryEdge(PointOnEdge point);
};


#endif //BUA_COMPLEXEDGE_H
