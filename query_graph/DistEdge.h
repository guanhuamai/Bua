//
// Created by mgh-PC on 2017/7/12.
//

#ifndef BUA_DISTEDGE_H
#define BUA_DISTEDGE_H

#include <vector>
using namespace std;


// DistEdge is the edge segment from edge in graph,
// value on x axis means the distance from start node of edge
// value on y axis means the distance from query point/ land mark to the point located on edge




class QueryEdge{
private:
    double leftX; // value on axis x of the left point
    double leftY; // value on axis y of the left point
    double rightX;
    double rightY;

    long long edgeID;

    static pair<double, double> kbLine(vector<double> twoEnds);

    static double lineIntersection(double k1, double b1, double k2, double b2);

public:

    QueryEdge(long long eid, double lx, double ly, double rx, double ry);

    vector<double> twoEnds();  // two ends of the segment, represented by a 4-tuple: (lx, ly, rx, ry)

    double intersectPositionOnX(QueryEdge e, double difference);  // return value less than zero is invalid

    double calDistByLine(double x);

    double lowBound();

    bool contains(double pos);
};

class DistEdge: public QueryEdge {
    long long queryID; // query point or landmark id

public:
    DistEdge(long long qid, long long eid, double lx, double ly, double rx, double ry);
};


#endif //BUA_DISTEDGE_H
