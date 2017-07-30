//
// Created by mgh-PC on 2017/7/29.
//

#include "KVCache.h"


KVCacheOnDisk::KVCacheOnDisk(string dbname) {
    KVCache::dbname = dbname;
    vl = new Villa(dbname.c_str(), Villa::OCREAT | Villa::OWRITER);
}

string KVCacheOnDisk::read(string key){

    try {
        return string(vl->get((const char *) &key, sizeof(int), NULL));
    }catch (Villa_error& e) {
        if (e.code() != Villa::ENOITEM) throw e;
    }

    return "";
}

void KVCacheOnDisk::write(string key, string value){
    try {
        vl->put(key.c_str(), sizeof(key), value.c_str(), sizeof(value), Villa::DOVER);
    }catch (Villa_error& e) { throw e; }
}

void KVCacheOnDisk::erase(string key){
    try{
        vl->out(key.c_str(), sizeof(key));
    }catch (Villa_error& e){
        if (e.code() != Villa::ENOITEM) throw e;
    }
}

KVCacheOnDisk::~KVCacheOnDisk(){
    vl->close();
    delete(vl);
    vl = NULL;
}

KVCacheOnMemory:: KVCacheOnMemory(string dbname){
    KVCache::dbname = dbname;
}

KVCacheOnMemory:: ~KVCacheOnMemory(){

}

string KVCacheOnMemory::read(string key){
    return cacheMap[key];
}

void KVCacheOnMemory::write(string key, string value){
    cacheMap[key] = value;
}

void KVCacheOnMemory::erase(string key){
    cacheMap.erase(key);
}



