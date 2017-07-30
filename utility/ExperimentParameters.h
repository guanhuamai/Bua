//
// Created by mgh-PC on 2017/7/18.
//

#ifndef BUA_EXPERIMENTPARAMETERS_H
#define BUA_EXPERIMENTPARAMETERS_H

#include "BUAConstants.h"
#include <functional>
using namespace std;

class ExperimentParameters{

private:
    ExperimentParameters(){}

public:

    static function<double (double, double)> aggFunction(){ return BUAConstants::maxFunction;}
    static double initialAggValue(){ return BUAConstants::initialAggregateValueMax();}
};

#endif //BUA_EXPERIMENTPARAMETERS_H
