//
// Created by mgh-PC on 2017/8/20.
//

#ifndef BUA_BRUTEFORCEGRAPH_H
#define BUA_BRUTEFORCEGRAPH_H

#include <vector>

using namespace std;

/**
 * provide function to find distance between two nodes
 */


class BruteForceGraph{

#define PLD pair<long long, double>
#define PEN pair<long long, pair<PLD, PLD>>

    vector<vector<long long>> nodes;  // sparse matrix
    vector<vector<double>> nodeDistance;  // sparse matrix distance
    vector<PEN> landmarks;
    int n;

public:
    double euclidDist(long long n1, long long n2);
    double landmarkDist(long long nodeID, long long lmrkID);
    BruteForceGraph(
            vector<vector<long long>> nodes,
            vector<vector<double>> nodeDistance,
            vector<PEN> landmarks
    );

};

#endif //BUA_BRUTEFORCEGRAPH_H
