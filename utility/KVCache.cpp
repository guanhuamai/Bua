//
// Created by mgh-PC on 2017/7/29.
//

#include "KVCache.h"
#include "BUAConstants.h"


KVCacheOnDisk::KVCacheOnDisk(string dbname) {
    KVCache::dbname = dbname;
    vl = new Villa(dbname.c_str(), Villa::OCREAT | Villa::OWRITER);
}

string KVCacheOnDisk::read(string key){
    try {
        char* valuePointer = vl->get(key.c_str(), (int) key.length(), NULL);
        int  valueSize = vl->vsiz(key.c_str(), (int) key.length());
        string res(valuePointer, (unsigned long) valueSize);
        delete valuePointer;
        return res;
    }catch (Villa_error& e) {
        cout << e.message() << endl;
        if (e.code() != Villa::ENOITEM) throw e;
    }

    return BUAConstants::EMPTY_STRING();
}

void KVCacheOnDisk::write(string key, string value){
    try {
        vl->put(key.c_str(), (int) key.length(), value.c_str(), (int) value.length(), Villa::DOVER);
    }catch (Villa_error& e) {
        cout << e.message() << endl;
        throw e;
    }
}

void KVCacheOnDisk::erase(string key){
    try{
        vl->out(key.c_str(), (int) key.length());
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



