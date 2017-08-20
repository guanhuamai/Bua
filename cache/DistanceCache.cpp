//
// Created by mgh-PC on 2017/7/30.
//

#include <sstream>
#include <iomanip>
#include "DistanceCache.h"
#include "../utility/BUAConstants.h"

DistanceCache::DistanceCache(const string &dbname) : KVCacheOnDisk(dbname) {}


string DistanceCache::nodeID2Key(long long snid, long long enid){
    stringstream ss;
    ss << setw(BUAConstants::PADDING_SIZE_LONGLONG()) << snid;
    ss << BUAConstants::DELIMINATOR2();
    ss << setw(BUAConstants::PADDING_SIZE_LONGLONG()) << enid;
    return ss.str();
}

pair<long long, long long> DistanceCache::key2NodeID(string key){
    istringstream iss(key);
    pair<long long, long long> res;
    iss >> res.first >> res.second;
    return res;
}

double DistanceCache::value2Distance(string value){
    istringstream distanceISS(value);
    if (value == BUAConstants::EMPTY_STRING())
        return BUAConstants::INVALID_DISTANCE();

    long long readableBuffer = 0;
    distanceISS >> readableBuffer;
    double res;
    memcpy(&res, &readableBuffer, sizeof(readableBuffer));
    return res;
}

string DistanceCache::distance2Value(double distance){
    long long readableBuffer = 0;
    memcpy(&readableBuffer, &distance, sizeof(distance));
    stringstream ss;
    ss << readableBuffer;
    return ss.str();
}


double DistanceCache::read(long long snid, long long enid){
    string key = nodeID2Key(snid, enid);
    return value2Distance(KVCacheOnDisk::read(key));
}

void DistanceCache::write(long long snid, long long enid, double distance){
    string key = nodeID2Key(snid, enid);
    string value = distance2Value(distance);
    KVCacheOnDisk::write(key, value);
}


void DistanceCache::erase(long long snid, long long enid){
    string key = nodeID2Key(snid, enid);
    KVCacheOnDisk::erase(key);
}
