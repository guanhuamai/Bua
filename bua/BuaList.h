//
// Created by mgh-PC on 2017/7/19.
//

#ifndef BUA_BUALIST_H
#define BUA_BUALIST_H


#include "QueryEdgePointer.h"
#include "../graph/Edge.h"
#include "../query_graph/ComplexEdge.h"
#include <vector>
#include <algorithm>
#include <set>

using namespace std;


class BuaList{
private:

    Graph* graph;

    vector<QueryEdgePointer> pointers;
    int currentEdgePos;

    vector<pair<PointOnEdge, pair<double, double>>> top;

    vector<pair<PointOnEdge, pair<double, double>>> candidates;

    double kthDistance;

    int k;

public:

    BuaList(vector<ComplexEdge>& edges);

    int where();

    void next();

    void last();

    double currentLowBound();

    vector<pair<PointOnEdge, pair<double, double>>> currentOnEdgePoints();

    bool inTop(PointOnEdge movingObject);
    bool inCandidates(PointOnEdge movingObject);
    int positionInTop(PointOnEdge movingObject);
    int positionInCandidates(PointOnEdge movingObject);

    void updateTop();
    void updateByInserting(PointOnEdge movingObjects, double aggregateValue, double lowBound);
    void updateByDeleting(PointOnEdge movingObjects);
    void forwardUpdate();
    void backwardUpdate();



    void bua(vector<PointOnEdge> deleteMovingObjects, vector<PointOnEdge> insertMovingObjects);

};



#endif //BUA_BUALIST_H
