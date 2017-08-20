//
// Created by mgh-PC on 2017/7/29.
//

#ifndef BUA_UTILITY_H
#define BUA_UTILITY_H


#include "../test/BruteForceGraph.h"

using namespace std;

class Utility{
private:
    template<typename Out>
    static void split(const std::string &s, char delim, Out result);

public:
    static vector<string> readLines(string fname);
    static vector<string> split(const std::string &s, char delim);
    static long long my_stoi(string s);
    static double my_stof(string s);
    static double abs(double x);
    static BruteForceGraph* buildBruteForceGraph(string nodeFile, string edgeFile, string landmarkFile);
};

#endif //BUA_UTILITY_H
