//
// Created by mgh-PC on 2017/7/19.
//

#include "QueryEdgePointer.h"

bool QueryEdgePointer::  operator < (QueryEdgePointer const & other){
    return minAggregateValue < other.minAggregateValue;
}

QueryEdgePointer::QueryEdgePointer(ComplexEdge* edge, QueryEdge* queryEdge){
    edgePointer = edge;
    queryEdgePointer = queryEdge;
    vector<double> twoEnds = queryEdgePointer->twoEnds();
    minAggregateValue = twoEnds[1];
    maxAggregateValue = twoEnds[3];
    if (minAggregateValue > maxAggregateValue)
        swap(minAggregateValue, maxAggregateValue);
}

double QueryEdgePointer::lowbound() {
    return minAggregateValue;
}

ComplexEdge* QueryEdgePointer::complexEdge(){
    return edgePointer;
}
QueryEdge* QueryEdgePointer::queryEdge(){
    return queryEdgePointer;
}
