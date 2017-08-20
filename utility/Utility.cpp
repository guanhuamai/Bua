//
// Created by mgh-PC on 2017/7/29.
//

#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include "Utility.h"
#include "BUAConstants.h"
#include "../graph/Node.h"

using namespace std;


template<typename Out>
void Utility::split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

vector<string> Utility::readLines(string fname){
    string line;
    ifstream myfile (fname.c_str());
    vector<string> res;
    if (myfile.is_open())
    {
        while ( getline (myfile,line)){
            res.push_back(line);
        }
        myfile.close();
    }
    else cout << "Unable to open file" << endl;
    return res;
}

vector<string> Utility::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    Utility::split(s, delim, back_inserter(elems));
    return elems;
}

long long Utility::my_stoi(string s){istringstream iss(s); long long res; iss >> res; return res;}
double Utility::my_stof(string s){istringstream iss(s); double res; iss >> res; return res;}


double Utility::abs(double x){ return x < 0 ? -x : x;}


BruteForceGraph* Utility::buildBruteForceGraph(string nodeFile, string edgeFile, string landmarkFile){

    vector<string> nodesStr = Utility::readLines(nodeFile);
    vector<string> edgesStr = Utility::readLines(edgeFile);
    vector<string> landmarkStr = Utility::readLines(landmarkFile);

    vector<vector<long long>> nodes (nodesStr.size(), vector<long long>());
    vector<vector<double >> nodeDistance(nodesStr.size(), vector<double>());
    vector<PEN> landmarks;


    for (size_t i = 1; i < edgesStr.size(); i++){
        vector<string> splitInfo = Utility::split(edgesStr[i], '\t');
        long long startNodeID = Utility::my_stoi(splitInfo[1]);
        long long endNodeID = Utility::my_stoi(splitInfo[2]);
        double edgeLength = Utility::my_stof(splitInfo[3]);
        nodes[startNodeID].push_back(endNodeID);
        nodes[endNodeID].push_back(startNodeID);
        nodeDistance[startNodeID].push_back(edgeLength);
        nodeDistance[endNodeID].push_back(edgeLength);
    }

    for (size_t i = 1; i < landmarkStr.size(); i++){
        vector<string> splitInfo = Utility::split(landmarkStr[i], '\t');
        long long startNodeID = Utility::my_stoi(splitInfo[0]);
        long long endNodeID = Utility::my_stoi(splitInfo[1]);
        long long edgeID = Utility::my_stoi(splitInfo[2]);
        double posStart = Utility::my_stof(splitInfo[3]);
        double posEnd = Utility::my_stof(splitInfo[4]);


        landmarks.push_back(PEN(edgeID, {PLD(startNodeID, posStart), PLD(endNodeID, posEnd)}));
    }

    return new BruteForceGraph(nodes, nodeDistance, landmarks);
}

