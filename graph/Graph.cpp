//
// Created by mgh-PC on 2017/7/11.
//

#include <queue>
#include <cfloat>
#include "Graph.h"
#include "../utility/BUAConstants.h"
#include "../query_graph/ComplexEdge.h"


void Graph::buildGraph() {
    constructNodeIndex(nodes);
    constructEdgeIndex(edges);
    for(auto& edge: edges){
        Node* startNode = nodes[nodePositionWithID[edge->getStartNodeID()]];
        Node* endNode = nodes[nodePositionWithID[edge->getEndNodeID()]];
        startNode->addAdjacentNode(endNode);
        startNode->addAdjacentEdge(edge);
        endNode->addAdjacentNode(startNode);
        endNode->addAdjacentEdge(edge);
    }

    distanceCache = new DistanceCache(BUAConstants::DEFAULT_DBNAME());
}


void Graph::addNode(long long id, double x, double y){
    nodes.push_back(new Node(id, x, y));
}



void Graph::addEdge(long long id, long long startNodeID, long long endNodeID, double edgeLength){
    edges.push_back(new Edge(id, startNodeID, endNodeID, edgeLength));
}


void Graph::constructNodeIndex(vector<Node*>& nodes){
    unordered_map<long long, size_t> mp;
    for(size_t i = 0; i < nodes.size(); i++){
        mp[nodes[i]->getID()] = i;
    }
    nodePositionWithID = mp;
};


void Graph::constructEdgeIndex(vector<Edge*>& edges){
    unordered_map<long long, size_t> mp;
    for(size_t i = 0; i < edges.size(); i++){
        mp[edges[i]->getID()] = i;
    }
    edgePositionWithID = mp;
}


Edge* Graph::getEdgeByID(long long edgeID){
    return edges[edgePositionWithID[edgeID]];
}

Node* Graph::getNodeByID(long long nodeID){
    return nodes[nodePositionWithID[nodeID]];
}


struct DistElement {
    long long nodeID;
    double dist;

    DistElement(long long nid, double d): nodeID(nid), dist(d){}

//    bool operator < (const DistElement& de) {
//        return dist < de.dist;
//    }
    DistElement(){
        nodeID = -1;
        dist = 0;
    }

    bool operator ()(const DistElement& de1, const DistElement& de2) {
        return de1.dist < de2.dist;
    }
};

double Graph::n2NDist(long long startNodeID, long long endNodeID) {
    if (startNodeID == endNodeID) return 0;

    double cacheDist = distanceCache->read(startNodeID, endNodeID);
    if (cacheDist >= 0){
        return cacheDist;
    }

    vector<bool > isVisit(nodes.size(), false);
    priority_queue<DistElement, vector<DistElement>, DistElement> heap;
    heap.push(DistElement(startNodeID, 0));
    isVisit[startNodeID] = true;

    while (!heap.empty()) {
        while (!heap.empty() && isVisit[heap.top().nodeID] )
            heap.pop();
        if (heap.empty()) break;

        auto curNode = heap.top();
        heap.pop();
        isVisit[curNode.nodeID] = true;

        distanceCache->write(startNodeID, curNode.nodeID, curNode.dist);  // write result to cache
        distanceCache->write(curNode.nodeID, startNodeID, curNode.dist);

        if (curNode.nodeID == endNodeID){
            return curNode.dist;
        }

        auto adjacentNodes = nodes[curNode.nodeID]->getAdjacentNodes();
        auto adjacentEdges = nodes[curNode.nodeID]->getAdjacentEdges();
        for (int i = 0; i < adjacentNodes.size(); i++ ){
            if (!isVisit[adjacentNodes[i]->getID()]){
                heap.push(DistElement(adjacentNodes[i]->getID(),
                                      adjacentEdges[i]->getEdgeLength()));
            }
        }
    }

    return DBL_MAX;
}

double Graph::p2NDist(long long eid, double pos, long long nodeID) {
    long long startNodeID = edges[eid]->getStartNodeID();
    long long endNodeID = edges[eid]->getEndNodeID();
    double edgeLength = edges[eid]->getEdgeLength();
    double ds = n2NDist(startNodeID, nodeID);
    double de = n2NDist(endNodeID, nodeID);

    double d1 = ds + pos;
    double d2 = de + edgeLength - pos;

    return min(d1, d2);  // 2 situations considered, nodeID can only connect from startNode or endNode
}

double abs(double d1, double d2){
    return d1 > d2 ? d1 - d2 : d2 - d1;
}

double Graph::p2pDist(long long eid1, double pos1, long long eid2, double pos2) {
    long long startNodeID = edges[eid2]->getStartNodeID();
    long long endNodeID = edges[eid2]->getEndNodeID();
    double edgeLength = edges[eid2]->getEdgeLength();

    double d1 = p2NDist(eid1, pos1, startNodeID) + pos2;
    double d2 = p2NDist(eid1, pos1, endNodeID) - pos2 + edgeLength;
    double d3 = eid1 == eid2 ? abs(d1, d2) : DBL_MAX;
    return min(d1, min(d2, d3));
}


void Graph::assignEdges(vector<Edge*> newEdges){
    dropEdges();
    edges = newEdges;
}
void Graph::assignNodes(vector<Node*> newNodes){
    dropNodes();
    nodes = newNodes;
}

void Graph::assignQueryPoint(vector<PointOnEdge*> queryPoints){
    for (auto queryPoint: queryPoints){
        ComplexEdge* cEdge = (ComplexEdge*)getEdgeByID(queryPoint->getEdgeID());
        cEdge->addLandmarks(queryPoint);
    }
}


void Graph::dropNodes(){
    if (nodes.size()!=0){
        for (int i = 0; i < nodes.size(); i++){
            delete nodes[i];
            nodes[i] = NULL;
        }
        nodes.clear();
    }
}
void Graph::dropEdges(){
    if (edges.size()!=0){
        for (int i = 0; i < edges.size(); i++){
            delete edges[i];
            edges[i] = NULL;
        }
        edges.clear();
    }
}

Graph::~Graph(){
    dropEdges();
    dropNodes();
    delete distanceCache;
    distanceCache = NULL;
}


