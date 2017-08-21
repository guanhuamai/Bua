//
// Created by mgh-PC on 2017/8/21.
//

#ifndef BUA_COMPLEXEDGETEST_H
#define BUA_COMPLEXEDGETEST_H


#include <gtest/gtest.h>
#include "../graph/Graph.h"
#include "../utility/Utility.h"
#include "BruteForceGraph.h"
#include "../query_graph/QueryGraphFactory.h"
#include "../utility/ExperimentParameters.h"

using namespace std;

class ComplexEdgeTest : public ::testing::Test {
protected:
    virtual void SetUp(){
        string nodeFile = "../data/test.cnode";
        string edgeFile = "../data/test.cedge";
        string queryFile = "../data/test.lmrk";
        vector<Node*> nodes = Node::nodeFromDiskFile(nodeFile);
        vector<Edge*> edges = Edge::edgeFromDiskFile(edgeFile);
        landmarks = PointOnEdge::queryPointFromDiskFile(queryFile);

        graph->assignNodes(nodes);
        graph->assignEdges(edges);
        graph->assignQueryPoint(landmarks);

        graph->buildGraph();
        cout << "set up finished" << endl;
    }

    virtual void TearDown(){
        delete(graph);
        graph = NULL;
    }
    vector<PointOnEdge*> landmarks;
    Graph* graph;
};



TEST_F(ComplexEdgeTest, SPLIT1){
    ExperimentParameters::setAggregateType(SUM);
    auto complexEdge4 = new ComplexEdge(3, 2, 3, 80);
    complexEdge4->splitByAggregateValue(landmarks, graph);
    auto landmarks = complexEdge4->getLandmarks();
    auto queryEdges = complexEdge4->getQueryEdges();
}

TEST_F(ComplexEdgeTest, SPLIT2){
    ExperimentParameters::setAggregateType(SUM);
    auto complexEdge4 = new ComplexEdge(3, 2, 3, 80);
    complexEdge4->splitByAggregateValue(landmarks, graph);
    auto landmarks = complexEdge4->getLandmarks();
    auto queryEdges = complexEdge4->getQueryEdges();
}

TEST_F(ComplexEdgeTest, SPLIT3){
    ExperimentParameters::setAggregateType(SUM);
    auto complexEdge4 = new ComplexEdge(3, 2, 3, 80);
    complexEdge4->splitByAggregateValue(landmarks, graph);
    auto landmarks = complexEdge4->getLandmarks();
    auto queryEdges = complexEdge4->getQueryEdges();
}

#endif //BUA_COMPLEXEDGETEST_H
