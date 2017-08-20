//
// Created by mgh-PC on 2017/8/20.
//


#include <set>
#include <algorithm>
#include <iostream>
#include "BruteForceGraph.h"
#include "../utility/BUAConstants.h"


bool cmp(pair<long long, double>& p1, pair<long long, double>& p2){
    return p1.second > p2.second;
}


double BruteForceGraph::landmarkDist(long long n, long long p){
    auto lmrk = landmarks[p];
    long long snid = lmrk.second.first.first;
    long long enid = lmrk.second.second.first;
    auto d1 = euclidDist(n, snid) + lmrk.second.first.second;
    auto d2 = euclidDist(n, enid) + lmrk.second.second.second;
    return min(d1, d2);
}

BruteForceGraph::BruteForceGraph(
        vector<vector<long long>> nodes,
        vector<vector<double>> nodeDistance,
        vector<PEN> landmarks
)
: nodes(nodes), nodeDistance(nodeDistance), landmarks(landmarks){n = (int)nodes.size();}


double BruteForceGraph::euclidDist(long long n1, long long n2){
    set<long long> isVisit;
    vector<pair<long long, double >> heap;
    heap.push_back(pair<long long, double >(n1, 0));
    while(!heap.empty()){
//        cout << isVisit.size() << endl;
        auto p = heap[0];
        pop_heap(heap.begin(), heap.end(), cmp);
        heap.pop_back();
        if (p.first == n2){
            return p.second;
        }
        if (isVisit.count(p.first) == 0){
            isVisit.insert(p.first);
            for(int i = 0; i < nodes[p.first].size(); i++){
                long long neighbour = nodes[p.first][i];
                double dist = nodeDistance[p.first][i] + p.second;
                if (isVisit.count(neighbour) == 0){
                    heap.push_back(pair<int,double >(neighbour, dist));
                }
            }
            make_heap(heap.begin(), heap.end(), cmp);
        }

    }

    return BUAConstants::INVALID_DISTANCE();

}


