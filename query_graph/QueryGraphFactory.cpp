//
// Created by mgh-PC on 2017/7/29.
//

#include <sstream>
#include <iostream>
#include "QueryGraphFactory.h"
#include "../utility/BUAConstants.h"




void QueryGraphFactory::combine(Graph* graph, vector<Node*>& rawNodes,
                                vector<Edge*>& rawEdges, vector<PointOnEdge*>& queryPoints){
    graph->assignNodes(rawNodes);
    graph->assignEdges(rawEdges);
    graph->buildGraph(); // build graph

    for (auto queryPoint: queryPoints){
        ComplexEdge* cEdge = (ComplexEdge*)graph->getEdgeByID(queryPoint->getEdgeID());
        cEdge->addLandmarks(queryPoint);
    }

    for (auto edge: rawEdges) {  // construct queryEdge information by split
        ComplexEdge *cEdge = (ComplexEdge *) edge;
        auto landmarks = cEdge->getLandmarks();
        if (landmarks.size() != 0){
            cout << cEdge->toString();
        }
    }

    for (auto edge: rawEdges){  // construct queryEdge information by split
        ComplexEdge* cEdge = (ComplexEdge*)edge;
        cEdge->splitByAggregateValue(queryPoints);
    }
}

Graph* QueryGraphFactory::graphFromDiskFile(const string nodeFile,
                                            const string edgeFile,
                                            const string queryPointFile) {
    Graph* graph = new Graph();
    vector<Node*> nodes = Node::nodeFromDiskFile(nodeFile);
    vector<Edge*> edges = Edge::edgeFromDiskFile(edgeFile);
    vector<PointOnEdge*> queryPoints = PointOnEdge::queryPointFromDiskFile(queryPointFile);

    vector<PointOnEdge*> sampleQueries = sampleLandmark(queryPoints);

    combine(graph, nodes, edges, sampleQueries);
    return graph;
}


vector<PointOnEdge*> QueryGraphFactory::takeTop(vector<PointOnEdge*> elements, int n){
    size_t s = elements.size();
    if (s < n) return elements;

    vector<PointOnEdge*> res;
    for (int i = 0; i < n; i++){
        res.push_back(elements[i]);
    }
    return res;
}

vector<PointOnEdge*> QueryGraphFactory::sampleLandmark(vector<PointOnEdge*> landmarks){
    if (BUAConstants::SAMPLE_SCHEME() == "taketop"){
        return takeTop(landmarks, BUAConstants::MAX_LANDMARKS());
    } else{

    }
    return landmarks;
}
