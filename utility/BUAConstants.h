//
// Created by mgh-PC on 2017/7/18.
//

#ifndef BUA_BUACONSTANTS_H
#define BUA_BUACONSTANTS_H


#include <cfloat>
using namespace std;

class BUAConstants{
private:
    BUAConstants(){};
public:

    static inline double DEVIATION() { return 0.00001; }
    static inline double initialAggregateValueMin = DBL_MAX;
    static inline double initialAggregateValueMax = DBL_MIN;
    static inline double initialAggregateValueSum = 0;
    static inline double minFunction(double a, double b) { return a < b ? a : b; }
    static inline double maxFunction(double a, double b) { return a > b ? a : b; }
    static inline double sumFunction(double a, double b) { return a + b; }

};

#endif //BUA_BUACONSTANTS_H
