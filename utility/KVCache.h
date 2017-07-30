//
// Created by mgh-PC on 2017/7/29.
//

#ifndef BUA_KVCACHE_H
#define BUA_KVCACHE_H


#include <algorithm>
#include <limits.h>
#include <float.h>
#include <xvilla.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <bitset>

using namespace std;
using namespace qdbm;

class KVCache{
protected:
    virtual string dbname;
public:
    virtual string read(string key) = 0;
    virtual void write(string key, string value) = 0;
    virtual void erase(string key) = 0;
};


class KVCacheOnDisk: public virtual KVCache{

private:
    Villa* vl;
protected:
    string read(string key);
    void write(string key, string value);
    void erase(string key);
public:
    KVCacheOnDisk(string dbname);
    ~KVCacheOnDisk();
};


class KVCacheOnMemory: public virtual KVCache{
    unordered_map<string, string> cacheMap;
public:
    KVCacheOnMemory(string dbname);
    ~KVCacheOnMemory();
    string read(string key);
    void write(string key, string value);
    void erase(string key);
};

#endif //BUA_KVCACHE_H
