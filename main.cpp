#include <iostream>
#include "bua/BuaList.h"
#include "query_graph/QueryGraphFactory.h"
#include "gtest/gtest.h"
#include "test/UnitTest.h"

void loadGraph(){
    string nodeFile = "../data/alaska.cnode";
    string edgeFile = "../data/alaska.cedge";
    string queryFile = "../data/alaska.lmrk";
    Graph* graph = QueryGraphFactory::graphFromDiskFile(nodeFile, edgeFile, queryFile);
    delete  graph;
    graph = NULL;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}