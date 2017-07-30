//
// Created by mgh-PC on 2017/7/29.
//

#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include "Utility.h"
#include "BUAConstants.h"

using namespace std;


template<typename Out>
void Utility::split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

vector<string> Utility::readLines(string fname){
    string line;
    ifstream myfile (fname.c_str());
    vector<string> res;
    if (myfile.is_open())
    {
        while ( getline (myfile,line)){
            res.push_back(line);
        }
        myfile.close();
    }
    else cout << "Unable to open file" << endl;
    return res;
}

vector<string> Utility::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    Utility::split(s, delim, back_inserter(elems));
    return elems;
}

long long Utility::my_stoi(string s){istringstream iss(s); long long res; iss >> res; return res;}
double Utility::my_stof(string s){istringstream iss(s); double res; iss >> res; return res;}

