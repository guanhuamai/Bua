//
// Created by mgh-PC on 2017/8/20.
//

#ifndef BUA_DISTEDGEUNITTEST_H
#define BUA_DISTEDGEUNITTEST_H

#include <gtest/gtest.h>
#include "../query_graph/DistEdge.h"
#include "../utility/BUAConstants.h"

using namespace std;

class DistEdgeTest : public ::testing::Test {

protected:
    virtual void SetUp(){
        a = new QueryEdge(0, 0.5, 0.5, 2, 2); // y = x
        b = new QueryEdge(0, 1.5, 0.5, 2.5, 1.5);  // y = x - 1
        c = new QueryEdge(0, 0.5, 2.5, 2.5, 0.5); // y = -x + 3
        d = new QueryEdge(0, 1, 0.5, 1, 3);  // x = 1
        e = new QueryEdge(0, 0.5, 1, 2.5, 1); // y = 1
        cout << "set up finished" << endl;
    }

    virtual void TearDown(){
        delete(a);
        delete(b);
        delete(c);
        delete(d);
        delete(e);
        a = NULL;
        b = NULL;
        c = NULL;
        d = NULL;
        e = NULL;
    }

    QueryEdge* a;
    QueryEdge* b;
    QueryEdge* c;
    QueryEdge* d;
    QueryEdge* e;
};

TEST_F(DistEdgeTest, DISTANCE){
    EXPECT_FLOAT_EQ(a->calDistByLine(0.2), 0.2);
    EXPECT_FLOAT_EQ(a->calDistByLine(0.4), 0.4);
    EXPECT_FLOAT_EQ(a->calDistByLine(0.6), 0.6);
    EXPECT_FLOAT_EQ(a->calDistByLine(1.2), 1.2);
    EXPECT_FLOAT_EQ(a->calDistByLine(2.4), 2.4);
    EXPECT_FLOAT_EQ(c->calDistByLine(0.6), 2.4);
    EXPECT_FLOAT_EQ(c->calDistByLine(2), 1);
    EXPECT_FLOAT_EQ(d->calDistByLine(1), BUAConstants::INFINITE_DOUBLE());
    EXPECT_FLOAT_EQ(c->calDistByLine(2), 1);
}


TEST_F(DistEdgeTest, INTERSECTION){
    EXPECT_FLOAT_EQ(a->intersectPositionOnX(*b, BUAConstants::DEVIATION()), BUAConstants::INVALID_DISTANCE());
    EXPECT_FLOAT_EQ(a->intersectPositionOnX(*c, BUAConstants::DEVIATION()), 1.5);
    EXPECT_FLOAT_EQ(a->intersectPositionOnX(*d, BUAConstants::DEVIATION()), 1);
    EXPECT_FLOAT_EQ(a->intersectPositionOnX(*e, BUAConstants::DEVIATION()), 1);

    EXPECT_FLOAT_EQ(c->intersectPositionOnX(*d, BUAConstants::DEVIATION()), 1);
    EXPECT_FLOAT_EQ(c->intersectPositionOnX(*b, BUAConstants::DEVIATION()), 2);

    EXPECT_FLOAT_EQ(d->intersectPositionOnX(*e, BUAConstants::DEVIATION()), 1);
}


#endif //BUA_DISTEDGEUNITTEST_H
