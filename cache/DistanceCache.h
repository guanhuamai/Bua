//
// Created by mgh-PC on 2017/7/30.
//

#ifndef BUA_DISTANCECACHE_H
#define BUA_DISTANCECACHE_H


#include "../utility/KVCache.h"

class DistanceCache: public virtual KVCacheOnDisk {
private:
    string nodeID2Key(long long snid, long long enid);
    pair<long long, long long> key2NodeID(string key);

    double value2Distance(string value);
    string distance2Value(double distance);
public:
    DistanceCache(const string &dbname);
    double read(long long snid, long long enid); // return -1 if not succeed
    void write(long long snid, long long enid, double distance);
    void erase(long long snid, long long enid);
};

#endif //BUA_DISTANCECACHE_H
