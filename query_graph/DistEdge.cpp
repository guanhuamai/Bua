//
// Created by mgh-PC on 2017/7/12.
//

#include "DistEdge.h"


QueryEdge::QueryEdge(long long eid, double lx, double ly, double rx, double ry) {
    edgeID = eid;
    leftX = lx;
    leftY = ly;
    rightX = rx;
    rightY = ry;
}



double QueryEdge::calDistByLine(double x){
    pair<double, double> kAndB = QueryEdge::kbLine(twoEnds());
    return kAndB.first * x + kAndB.second;  // return kx + b
}

DistEdge::DistEdge(long long qid, long long eid,
                   double lx, double ly, double rx, double ry) : QueryEdge(eid, lx, ly, rx, ry) {
    queryID = qid;
}

vector<double> QueryEdge::twoEnds(){
    return vector<double>{leftX, leftY, rightX, rightY};
}


pair<double, double> QueryEdge::kbLine(vector<double> twoEnds){
    double k = (twoEnds[1] - twoEnds[3]) / (twoEnds[0] - twoEnds[2]);
    double b = twoEnds[1] - k * twoEnds[0];
    return pair<double, double >(k, b);
}


double QueryEdge::lineIntersection(double k1, double b1, double k2, double b2){
    return (b2 - b1) / (k1 - k2);
}


double QueryEdge::intersectPositionOnX(QueryEdge e, double difference) {
    vector<double> ends = twoEnds();
    vector<double> eEnds = e.twoEnds();

    pair<double, double> line1 = kbLine(ends);
    pair<double, double> line2 = kbLine(eEnds);
    double pos = QueryEdge::lineIntersection(line1.first, line1.second, line2.first, line2.second);

    if (pos < ends[0] - difference || pos > (ends[2] + difference)
        || pos < eEnds[0] - difference || pos > (eEnds[2] + difference)){
        return -1;
    }

    // eliminates the difference
    pos = min(pos, ends[2]);
    pos = min(pos, eEnds[2]);
    pos = max(pos, ends[0]);
    pos = max(pos, eEnds[0]);

    return pos;
}

