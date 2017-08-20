//
// Created by mgh-PC on 2017/7/13.
//

#include <iostream>
#include "PointOnEdge.h"
#include "../utility/Utility.h"


long long PointOnEdge::getID() const {
    return id;
}

double PointOnEdge::getPosition() const {
    return pos;
}

long long PointOnEdge::getEdgeID() const {
    return edgeID;
}


string PointOnEdge:: toString(){
    string s;
    s += "id: " + to_string(id) + "edge id: " + to_string(edgeID) + " position: " + to_string(pos) + "\n";
    return s;
}


vector<PointOnEdge*> PointOnEdge::queryPointFromDiskFile(const string queryPointFile){
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
