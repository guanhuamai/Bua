//
// Created by mgh-PC on 2017/7/29.
//

#ifndef BUA_QUERYGRAPHFACTORY_H
#define BUA_QUERYGRAPHFACTORY_H


#include "../graph/Graph.h"
#include "../graph/PointOnEdge.h"
#include "../utility/Utility.h"
#include "ComplexEdge.h"
#include <vector>

using namespace std;

class QueryGraphFactory {
    static vector<Node*> nodeFromDiskFile(const string nodeFile);
    static vector<Edge*> edgeFromDiskFile(const string edgeFile);
    static vector<PointOnEdge*> queryPointFromDiskFile(const string queryPointFile);
    static void combine(Graph* graph, vector<Node*>& rawNodes,
                        vector<Edge*>& rawEdges, vector<PointOnEdge*>& queryPoints);


    static vector<PointOnEdge*> takeTop(vector<PointOnEdge*> elements, int n);
    static vector<PointOnEdge*> sampleLandmark(vector<PointOnEdge*> landmarks);
public:
    static Graph* graphFromDiskFile(const string nodeFile, const string edgeFile, const string queryPointFile);
};

#endif //BUA_QUERYGRAPHFACTORY_H
