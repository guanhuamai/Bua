//
// Created by mgh-PC on 2017/7/13.
//

#include <iostream>
#include "ComplexEdge.h"
#include <cmath>
#include <algorithm>
#include "../utility/ExperimentParameters.h"

using namespace std;



vector<DistEdge> ComplexEdge::splitByDist(PointOnEdge landmark, Graph* graph){
    vector<DistEdge> segmentDistEdges;
    double ds = graph->p2NDist(landmark.getEdgeID(), landmark.getPosition(), getStartNodeID());
    double de = graph->p2NDist(landmark.getEdgeID(), landmark.getPosition(), getEndNodeID());


    if (abs(ds - de) < 0.00001){
        segmentDistEdges.push_back(
            DistEdge(landmark.getID(), landmark.getEdgeID(), 0, ds, landmark.getPosition(), de)
        );
    }else{
        double x = (de - ds + getEdgeLength()) / 2;
        double y = (de + ds + getEdgeLength()) / 2;

        if (landmark.getEdgeID() == getID()) { // if it is the same edge, there will be 3 segments of edges
            pair<double, double> firstPoint(x, y);
            pair<double, double> secondPoint(landmark.getPosition(), 0);

            if (x > landmark.getPosition())  swap(firstPoint, secondPoint);

            segmentDistEdges.push_back(
                    DistEdge(landmark.getID(), landmark.getEdgeID(), 0, ds, firstPoint.first, firstPoint.second));
            segmentDistEdges.push_back(
                    DistEdge(landmark.getID(), landmark.getEdgeID(), firstPoint.first, firstPoint.second,
                             secondPoint.first, secondPoint.second));

            segmentDistEdges.push_back(
                    DistEdge(landmark.getID(), landmark.getEdgeID(), secondPoint.first, secondPoint.second,
                             getEdgeLength(), de));

        } else {  // if landmark is not on edge, then there will only be 2 segments of edge
            segmentDistEdges.push_back(DistEdge(landmark.getID(), landmark.getEdgeID(), 0, ds, x, y));
            segmentDistEdges.push_back(DistEdge(landmark.getID(), landmark.getEdgeID(), x, y, getEdgeLength(), de));
        }

    }

    return segmentDistEdges;
}


void ComplexEdge::splitByDist(vector<PointOnEdge*>& landmarks, Graph* graph){
    distEdges.clear();
    for (auto &landmark: landmarks){
        distEdges.push_back(splitByDist(*landmark, graph));
    }
}


ComplexEdge::ComplexEdge(long long int id, long long int startNodeID, long long int endNodeID, double edgeLength)
        : Edge(id, startNodeID, endNodeID, edgeLength) {
}


void ComplexEdge::splitByAggregateValue(vector<PointOnEdge*>& landmarks, Graph* graph) {
    splitByDist(landmarks, graph);
    aggregateDistEdges();
}


double ComplexEdge::calculateAggregateWithDistEdges(double pos){
    double aggregateValue = ExperimentParameters::initialAggValue();
    for (auto& dEdges: distEdges){
        for (auto& dEdge: dEdges){
            vector<double> twoEnds = dEdge.twoEnds();
            if (twoEnds[0] < pos && pos < twoEnds[2]){
                aggregateValue = ExperimentParameters::aggFunction()(aggregateValue, dEdge.calDistByLine(pos));
                break;
            }
        }
    }

    return aggregateValue;
}

void ComplexEdge::aggregateDistEdges(){ // assume distEdges have been finished
    vector<double> lineIntersections;
    for(auto &dEdges: distEdges){ // place all position of X-axis into lineIntersections
        for(auto &dEdge: dEdges){
            lineIntersections.push_back(dEdge.twoEnds()[0]); // x position of the left end
            lineIntersections.push_back(dEdge.twoEnds()[2]); // x position of the right end
        }
    }
    for (size_t i = 0; i < distEdges.size(); i++){  // place all intersection x into lineIntersections
        for (size_t j = 0; j < distEdges[i].size(); j++){
            for(size_t i1 = i + 1; i1 < distEdges.size(); i1++){
                for (size_t j1 = 0; j1 < distEdges[i1].size(); j1++){
                    auto& segment1 = distEdges[i][j];
                    auto& segment2 = distEdges[i1][j1];
                    double intersectX = segment1.intersectPositionOnX(segment2, BUAConstants::DEVIATION());

                    if (intersectX > 0) lineIntersections.push_back(intersectX);
                }
            }
        }
    }

    sort(lineIntersections.begin(), lineIntersections.end());

    size_t pos = 0;
    while (pos < lineIntersections.size() - 1){ // remove duplicates
        size_t nextPos = pos + 1;
        if (abs(lineIntersections[pos] - lineIntersections[nextPos]) < BUAConstants::DEVIATION())
            lineIntersections.erase(lineIntersections.begin() + nextPos);
        else pos = nextPos;
    }

    queryEdges.clear();  // insert aggregate segments into queryEdges
    double lastX = lineIntersections[0];
    double lastY = calculateAggregateWithDistEdges(lastX);

    for (size_t i = 1; i < lineIntersections.size(); i++){
        double x = lineIntersections[i];
        double y = calculateAggregateWithDistEdges(x);

        queryEdges.push_back(QueryEdge(getID(), lastX, lastY, x, y));
    }

}


vector<QueryEdge> ComplexEdge::getQueryEdges() {
    return queryEdges;
}

//vector<QueryEdgePointer> ComplexEdge::queryEdgePointers(){
//    vector<QueryEdgePointer> pointers;
//    for(size_t i = 0; i < queryEdges.size(); i++){
//        pointers.push_back(QueryEdgePointer(&queryEdges[i]));
//    }
//    return pointers;
//}



vector<PointOnEdge> ComplexEdge::getLandmarks(){
    return landmarksOnEdge;
}

vector<PointOnEdge> ComplexEdge::getMovingObjects(){
    return movingObjectsOnEdge;
}

QueryEdge* ComplexEdge::getQueryEdge(PointOnEdge point){
    if (point.getEdgeID() == id){
        for (int i = 0; i < queryEdges.size(); i++){
            if (queryEdges[i].contains(point.getPosition() )){
                return &queryEdges[i];
            }
        }
        return NULL;
    } else {
        return NULL;
    }
}

void ComplexEdge::addLandmarks(PointOnEdge* landmark){
    landmarksOnEdge.push_back(*landmark);
}


string ComplexEdge::toString(){
    string s;

    s += "edge info: " + Edge::toString();

    s += "query edges: \n";
    for(auto qEdge: queryEdges)
        s += qEdge.toString();

    s += "\n\n dist edges: \n";
    for(auto dEdges: distEdges){
        for(auto dEdge: dEdges)
            s += dEdge.toString();
        s += "------------\n";
    }

    s += "\n\n moving objects: \n";
    for (auto mObj: movingObjectsOnEdge){
        s += mObj.toString();
    }

    s += "\n\n landmarks objects: \n";
    for (auto lmrk: landmarksOnEdge){
        s += lmrk.toString();
    }

    s += "\n\n";
    return s;
}
