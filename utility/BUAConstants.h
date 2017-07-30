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
    static inline double initialAggregateValueMin() { return DBL_MAX; }
    static inline double initialAggregateValueMax() { return  DBL_MIN;}
    static inline double initialAggregateValueSum() { return 0;}
    static inline double minFunction(double a, double b) { return a < b ? a : b; }
    static inline double maxFunction(double a, double b) { return a > b ? a : b; }
    static inline double sumFunction(double a, double b) { return a + b; }
    static inline int MAX_LANDMARKS() { return 5;}
    static inline string SAMPLE_SCHEME(){ return "taketop";}
    static inline int PADDING_SIZE_LONGLONG(){ return 20;}
    static inline char DELIMINATOR1(){return '\t';}
    static inline char DELIMINATOR2(){return ' ';}
    static inline string DEFAULT_DBNAME(){ return "default.database";}

};

#endif //BUA_BUACONSTANTS_H
