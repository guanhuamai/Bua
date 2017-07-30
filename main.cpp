#include <iostream>
#include "bua/BuaList.h"
#include "query_graph/QueryGraphFactory.h"
int main() {
    string nodeFile = "../data/alaska.cnode";
    string edgeFile = "../data/alaska.cedge";
    string queryFile = "../data/alaska.lmrk";
    Graph* graph = QueryGraphFactory::graphFromDiskFile(nodeFile, edgeFile, queryFile);
    delete  graph;
    graph = NULL;

    return 0;
}