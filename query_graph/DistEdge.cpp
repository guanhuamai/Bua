//
// Created by mgh-PC on 2017/7/12.
//

#include "DistEdge.h"
#include "../utility/Utility.h"
#include "../utility/BUAConstants.h"


QueryEdge::QueryEdge(long long eid, double lx, double ly, double rx, double ry) {
    edgeID = eid;
    leftX = lx;
    leftY = ly;
    rightX = rx;
    rightY = ry;
}



double QueryEdge::calDistByLine(double x){
    if (!contains(x)){
        return BUAConstants::INVALID_DISTANCE();
    }
    pair<double, double> kAndB = QueryEdge::kbLine(twoEnds());
    if (kAndB.first == BUAConstants::INFINITE_DOUBLE()){
        return BUAConstants::INFINITE_DOUBLE();
    }
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
    double diffX = (twoEnds[0] - twoEnds[2]);
    double diffY = (twoEnds[1] - twoEnds[3]);
    if (Utility::abs(diffX) < BUAConstants::DEVIATION()){
        return pair<double, double >(BUAConstants::INFINITE_DOUBLE(), twoEnds[0]);
    }
    double k = diffY / diffX;
    double b = twoEnds[1] - k * twoEnds[0];
    return pair<double, double >(k, b);
}


double QueryEdge::lineIntersection(double k1, double b1, double k2, double b2){
    if (k1 == BUAConstants::INFINITE_DOUBLE()){
        double x = b1; // in kbLine function, when k1 = INF b1 saves the x value
        return x;
    }else if (k2 == BUAConstants::INFINITE_DOUBLE()){
        double x = b2; // in kbLine function, when k1 = INF b1 saves the x value
        return x;

    } else{
        return (b2 - b1) / (k1 - k2);
    }
}


double QueryEdge::intersectPositionOnX(QueryEdge e, double difference) {
    vector<double> ends = twoEnds();
    vector<double> eEnds = e.twoEnds();

    pair<double, double> line1 = kbLine(ends);
    pair<double, double> line2 = kbLine(eEnds);
    double pos = QueryEdge::lineIntersection(line1.first, line1.second, line2.first, line2.second);

    if (pos < ends[0] - difference || pos > (ends[2] + difference)
        || pos < eEnds[0] - difference || pos > (eEnds[2] + difference)){
        return BUAConstants::INVALID_DISTANCE();
    }

    // eliminates the difference
    pos = min(pos, ends[2]);
    pos = min(pos, eEnds[2]);
    pos = max(pos, ends[0]);
    pos = max(pos, eEnds[0]);

    return pos;
}

double QueryEdge::lowBound(){
    return min(leftY, rightY);
}

bool QueryEdge::contains(double pos){
    return (leftX <= pos || pos <= rightX);
}


string DistEdge::toString() {
    string s;
    s += "qid: " + to_string(queryID) + " extends from super ----\n"
         + "-----------" + QueryEdge::toString();
    return s;
}


string QueryEdge::toString() {
    string s;
    s += "edge id: " + to_string(edgeID)
         + "left x: " + to_string(leftX)
         + "left y: " + to_string(leftY)
         + "right x: " + to_string(rightX)
         + "right y: " + to_string(rightY)
         + "\n";
    return s;
}
