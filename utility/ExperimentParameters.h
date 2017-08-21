//
// Created by mgh-PC on 2017/7/18.
//

#ifndef BUA_EXPERIMENTPARAMETERS_H
#define BUA_EXPERIMENTPARAMETERS_H

#include "BUAConstants.h"
#include <functional>
using namespace std;

enum AGGREGATE_TYPE{SUM, MIN, MAX};

class ExperimentParameters{

private:
    ExperimentParameters(){}

    static AGGREGATE_TYPE aggType;

public:

    static void setAggregateType(AGGREGATE_TYPE aggregateType){aggType = aggregateType;}

    static function<double (double, double)> aggFunction() {
        if (aggType == SUM){
            return BUAConstants::sumFunction;
        } else if (aggType == MIN){
            return BUAConstants::minFunction;
        } else {
            return BUAConstants::maxFunction;
        }
    }

    static double initialAggValue(){
        if (aggType == SUM){
            return BUAConstants::initialAggregateValueSum();
        } else if (aggType == MIN){
            return BUAConstants::initialAggregateValueMin();
        } else{
            return BUAConstants::initialAggregateValueMax();
        }
    }
};

#endif //BUA_EXPERIMENTPARAMETERS_H
