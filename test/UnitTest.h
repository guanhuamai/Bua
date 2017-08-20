//
// Created by mgh-PC on 2017/7/30.
//

#ifndef BUA_UNITTEST_H
#define BUA_UNITTEST_H

#include <gtest/gtest.h>
#include "../cache/DistanceCache.h"
#include "../utility/BUAConstants.h"
#include "../graph/graph.h"
#include "../query_graph/QueryGraphFactory.h"

using namespace std;

TEST(CACHE_TEST, BASIC_READ_WRITE){

    auto dc = new DistanceCache(BUAConstants::DEFAULT_DBNAME());
    double d1 = 10.0;
    double d2 = DBL_MAX;
    double d3 = DBL_MIN;
    double d4 = 0;

    long long a1 = 11231231;
    long long a2 = LLONG_MAX;
    long long a3 = LLONG_MIN;
    long long a4 = 0;

    long long b1 = 11231231;
    long long b2 = LLONG_MAX;
    long long b3 = LLONG_MIN;
    long long b4 = 0;

    dc->write(a1, b1, d1);
    EXPECT_EQ(d1, dc->read(a1, b1));
    dc->write(a2, b2, d2);
    EXPECT_FLOAT_EQ(d2, dc->read(a2, b2));
    dc->write(a3, b3, d3);
    EXPECT_FLOAT_EQ(d3, dc->read(a3, b3));
    dc->write(a4, b4, d4);
    EXPECT_FLOAT_EQ(d1, dc->read(a1, b1));
    EXPECT_FLOAT_EQ(d2, dc->read(a2, b2));
    EXPECT_FLOAT_EQ(d3, dc->read(a3, b3));
    EXPECT_FLOAT_EQ(d4, dc->read(a4, b4));

    dc->erase(a1, b1);
    EXPECT_FLOAT_EQ(BUAConstants::INVALID_DISTANCE(), dc->read(a1, b1));
    dc->erase(a2, b2);
    EXPECT_FLOAT_EQ(BUAConstants::INVALID_DISTANCE(), dc->read(a2, b2));
    dc->erase(a3, b3);
    EXPECT_FLOAT_EQ(BUAConstants::INVALID_DISTANCE(), dc->read(a3, b3));
    EXPECT_FLOAT_EQ(d4, dc->read(a4, b4));

}


class GraphTest : public ::testing::Test {
protected:
    virtual void SetUp(){
        string nodeFile = "../data/alaska.cnode";
        string edgeFile = "../data/alaska.cedge";
        string queryFile = "../data/alaska.lmrk";

        vector<Node*> nodes = Node::nodeFromDiskFile(nodeFile);
        vector<Edge*> edges = Edge::edgeFromDiskFile(edgeFile);
        vector<PointOnEdge*> landmarks = PointOnEdge::queryPointFromDiskFile(queryFile);

        graph->assignNodes(nodes);
        graph->assignEdges(edges);
        graph->assignQueryPoint(landmarks);

        graph->buildGraph();
    }

    virtual void TearDown(){
        delete(graph);
        graph = NULL;
    }

    Graph* graph;
};


TEST_F(GraphTest, DISTANCE){
    graph->n2NDist(0, 0);
    graph->n2NDist(200, 500);
    graph->n2NDist(10, 10000);
    graph->n2NDist(3000, 3005);
    graph->n2NDist(600, 20000);
}


TEST_F(GraphTest, DISTANCE2){

}




#endif //BUA_UNITTEST_H
