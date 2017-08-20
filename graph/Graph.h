//
// Created by mgh-PC on 2017/7/11.
//

#ifndef BUA_GRAPH_H
#define BUA_GRAPH_H

#include <vector>
#include <unordered_map>
#include "Edge.h"
#include "Node.h"
#include "../cache/DistanceCache.h"
#include "PointOnEdge.h"

using namespace std;


class Graph{
private:
    vector<Edge*> edges;
    vector<Node*> nodes;
    vector<PointOnEdge*> queryPoints;
    unordered_map<long long, size_t> nodePositionWithID;
    unordered_map<long long, size_t> edgePositionWithID;
    DistanceCache* distanceCache;

    void constructNodeIndex(vector<Node*>& nodes);
    void constructEdgeIndex(vector<Edge*>& edges);

    void dropNodes();
    void dropEdges();

public:
    ~Graph();

    Edge* getEdgeByID(long long edgeID);
    Node* getNodeByID(long long nodeID);
    PointOnEdge* getQueryPointByID(long long qID);

//    void addEdge(Edge* edge);
    void addEdge(long long id, long long startNodeID, long long endNodeID, double edgeLength);
    void addNode(long long id, double x, double y);

    void assignEdges(vector<Edge*> edges);
    void assignNodes(vector<Node*> nodes);
    void assignQueryPoint(vector<PointOnEdge*> queryPoints);

    void buildGraph();
    double n2NDist(long long startNodeID, long long endNodeID);
    double p2NDist(long long eid, double pos, long long nodeID);
    double p2pDist(long long eid, double pos, long long eid2, double pos2);

};





#endif //BUA_GRAPH_H
