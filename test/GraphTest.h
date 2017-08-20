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
        graph = new Graph();
        bfGraph = Utility::buildBruteForceGraph(nodeFile, edgeFile, queryFile);

        vector<Node*> nodes = Node::nodeFromDiskFile(nodeFile);
        vector<Edge*> edges = Edge::edgeFromDiskFile(edgeFile);
        vector<PointOnEdge*> landmarks = PointOnEdge::queryPointFromDiskFile(queryFile);

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

    Graph* graph;
    BruteForceGraph* bfGraph;
};


TEST_F(GraphTest, DISTANCE1){
    long long qid1 = 0;
    auto lmrk1 = graph->getQueryPointByID(qid1);
    long long qid2 = 10;
    auto lmrk2 = graph->getQueryPointByID(qid2);
    long long qid3 = 100;
    auto lmrk3 = graph->getQueryPointByID(qid3);
    long long qid4 = 1000;
    auto lmrk4 = graph->getQueryPointByID(qid4);
    long long qid5 = 500;
    auto lmrk5 = graph->getQueryPointByID(qid5);

    EXPECT_FLOAT_EQ( bfGraph->landmarkDist(0,qid1),
                     graph->p2NDist(lmrk1->getEdgeID(), lmrk1->getPosition(), 0));
    EXPECT_FLOAT_EQ( bfGraph->landmarkDist(123,qid2),
                     graph->p2NDist(lmrk2->getEdgeID(), lmrk2->getPosition(), 123));
    EXPECT_FLOAT_EQ( bfGraph->landmarkDist(54,qid3),
                     graph->p2NDist(lmrk3->getEdgeID(), lmrk3->getPosition(), 54));
    EXPECT_FLOAT_EQ( bfGraph->landmarkDist(5676,qid4),
                     graph->p2NDist(lmrk4->getEdgeID(), lmrk4->getPosition(), 5676));
    EXPECT_FLOAT_EQ( bfGraph->landmarkDist(20000,qid5),
                     graph->p2NDist(lmrk5->getEdgeID(), lmrk5->getPosition(), 20000));

}

TEST_F(GraphTest, DISTANCE2){
    EXPECT_FLOAT_EQ( bfGraph->euclidDist(0,0), graph->n2NDist(0, 0));
    EXPECT_FLOAT_EQ( bfGraph->euclidDist(10, 10000), graph->n2NDist(10, 10000));
    EXPECT_FLOAT_EQ( bfGraph->euclidDist(3000, 3005), graph->n2NDist(3000, 3005));
    EXPECT_FLOAT_EQ( graph->n2NDist(200, 500), bfGraph->euclidDist(200, 500));
    EXPECT_FLOAT_EQ( bfGraph->euclidDist(600, 20000), graph->n2NDist(600, 20000));
}






#endif //BUA_UNITTEST_H
