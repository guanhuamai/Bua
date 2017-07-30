//
// Created by mgh-PC on 2017/7/29.
//

#include <sstream>
#include <iostream>
#include "QueryGraphFactory.h"
#include "../utility/BUAConstants.h"

vector<Node*> QueryGraphFactory::nodeFromDiskFile(const string nodeFile){
    vector<Node*> res;
    vector<string> nodesStr = Utility::readLines(nodeFile);
    for (size_t i = 1; i < nodesStr.size(); i++){
        vector<string> splitInfo = Utility::split(nodesStr[i], '\t');
        long long nodeID = Utility::my_stoi(splitInfo[0]);
        double nodeX = Utility::my_stof(splitInfo[1]);
        double nodeY = Utility::my_stof(splitInfo[2]);
        res.push_back(new Node(nodeID, nodeX, nodeY));
    }
    cout << "input nodes: " << res.size() << endl;
    return  res;
}

vector<Edge*> QueryGraphFactory::edgeFromDiskFile(const string edgeFile){
    vector<Edge*> res;
    vector<string> edgesStr = Utility::readLines(edgeFile);
    for (size_t i = 1; i < edgesStr.size(); i++){
        vector<string> splitInfo = Utility::split(edgesStr[i], '\t');
        long long edgeID = Utility::my_stoi(splitInfo[0]);
        long long startNodeID = Utility::my_stoi(splitInfo[1]);
        long long endNodeID = Utility::my_stoi(splitInfo[2]);
        double edgeLength = Utility::my_stof(splitInfo[3]);
        res.push_back(new ComplexEdge(edgeID, startNodeID, endNodeID, edgeLength)); // use ComplexEdge
    }
    cout << "input edges: " << res.size() << endl;
    return res;
}

vector<PointOnEdge*> QueryGraphFactory::queryPointFromDiskFile(const string queryPointFile){
    vector<PointOnEdge*> res;
    vector<string> queriesStr = Utility::readLines(queryPointFile);
    for (size_t i = 1; i < queriesStr.size(); i++){
        vector<string> splitInfo = Utility::split(queriesStr[i], '\t');
        long long startNodeID = Utility::my_stoi(splitInfo[0]);
        long long endNodeID = Utility::my_stoi(splitInfo[1]);
        long long edgeID = Utility::my_stoi(splitInfo[2]);
        double posStart = Utility::my_stof(splitInfo[3]);
        double posEnd = Utility::my_stof(splitInfo[4]);

        long long queryID = (long long) i - 1;
        res.push_back(new PointOnEdge(queryID, posStart, edgeID));
    }
    cout << "input queries: " << res.size() << endl;
    return res;
}

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

Graph* QueryGraphFactory::graphFromDiskFile(const string nodeFile, const string edgeFile,
                                               const string queryPointFile) {
    Graph* graph = new Graph();
    vector<Node*> nodes = QueryGraphFactory::nodeFromDiskFile(nodeFile);
    vector<Edge*> edges = QueryGraphFactory::edgeFromDiskFile(edgeFile);
    vector<PointOnEdge*> queryPoints = QueryGraphFactory::queryPointFromDiskFile(queryPointFile);

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
