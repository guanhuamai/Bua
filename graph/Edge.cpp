//
// Created by mgh-PC on 2017/7/11.
//

#include "Edge.h"
#include "../utility/Utility.h"
#include "../query_graph/ComplexEdge.h"


string Edge::toString(){

    string s;
    s += "edge id: " + to_string(id)
         + "start node: " + to_string(startNodeID)
         + "end node: " + to_string(endNodeID)
         + "edge length: " + to_string(edgeLength)
         + "\n";
    return s;

}

long long Edge::getID() const{
    return id;
}

Edge::Edge(long long id, long long startNodeID, long long endNodeID, double edgeLength){
    this->id = id;
    this->startNodeID = startNodeID;
    this->endNodeID = endNodeID;
    this->edgeLength = edgeLength;
}

long long Edge::getStartNodeID() const {
    return startNodeID;
}


long long Edge::getEndNodeID() const {
    return endNodeID;
}

double Edge::getEdgeLength() const {
    return edgeLength;
}

long long Edge::getOppositeNodeID(long long nodeID) const {
    if (nodeID == startNodeID){
        return endNodeID;
    } else if (nodeID == endNodeID){
        return startNodeID;
    } else {
        return -1;
    }
}


vector<Edge*> Edge::edgeFromDiskFile(const string edgeFile){
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
