//
// Created by mgh-PC on 2017/7/19.
//

#ifndef BUA_QUERYEDGEPOINTER_H
#define BUA_QUERYEDGEPOINTER_H

#include "../query_graph/DistEdge.h"
#include "../query_graph/ComplexEdge.h"

class QueryEdgePointer{
private:
    ComplexEdge* edgePointer;
    QueryEdge* queryEdgePointer;
    double minAggregateValue;
    double maxAggregateValue;

public:

    bool operator < (QueryEdgePointer const & other);

    QueryEdgePointer(ComplexEdge* edge, QueryEdge* queryEdge);

    double lowbound();

    ComplexEdge* complexEdge();
    QueryEdge* queryEdge();

};
#endif //BUA_QUERYEDGEPOINTER_H
