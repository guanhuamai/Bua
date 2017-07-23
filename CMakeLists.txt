cmake_minimum_required(VERSION 3.7)
project(Bua)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp graph/Edge.cpp graph/Edge.h graph/Node.cpp graph/Node.h graph/Graph.cpp graph/Graph.h query_graph/DistEdge.cpp query_graph/DistEdge.h query_graph/ComplexEdge.cpp query_graph/ComplexEdge.h graph/PointOnEdge.cpp graph/PointOnEdge.h utility/BUAConstants.h utility/ExperimentParameters.h bua/QueryEdgePointer.cpp bua/QueryEdgePointer.h bua/BuaList.cpp bua/BuaList.h)
add_executable(Bua ${SOURCE_FILES})