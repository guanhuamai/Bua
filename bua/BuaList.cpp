//
// Created by mgh-PC on 2017/7/19.
//

#include <cfloat>
#include "BuaList.h"



BuaList::BuaList(vector<ComplexEdge> &edges) {
    pointers.clear();
    for(auto& edge: edges){
        vector<QueryEdge>& queryEdges = edge.getQueryEdges();
        for(size_t i = 0; i < queryEdges.size(); i++){
            pointers.push_back(QueryEdgePointer(&edge, &queryEdges[i]));
        }
    }
    sort(pointers.begin(), pointers.end());
    currentEdgePos = 0;
}


int BuaList::where(){
    if (currentEdgePos < 0 || currentEdgePos >= pointers.size()){
        return -1;
    }
    return currentEdgePos;
}

void BuaList::next(){
    currentEdgePos ++;
}

void BuaList::last(){
    currentEdgePos --;
}


double BuaList::currentLowBound() {
    try{
        return pointers[currentEdgePos].lowbound();
    }catch (exception e){
        printf("pointer position illegal: %d", currentEdgePos);
        throw e;
    }
}


vector<pair<PointOnEdge, pair<double, double>>> BuaList::currentOnEdgePoints(){
    vector<PointOnEdge> allMovingObjects = pointers[currentEdgePos].complexEdge()->getMovingObjects();

    auto queryEdge = *pointers[currentEdgePos].queryEdge();
    vector<double> twoEnds = queryEdge.twoEnds();
    vector<pair<PointOnEdge, pair<double, double>>> movingObjects;
    for (auto movingObject: allMovingObjects){
        if (movingObject.getPosition() > twoEnds[0] && movingObject.getPosition() < twoEnds[2] ){
            movingObjects.push_back(pair<PointOnEdge,
                    pair<double, double>>(movingObject,
                                          pair<double, double>(queryEdge.calDistByLine(movingObject.getPosition()),
                                                               currentLowBound())));
        }
    }
    return movingObjects;
}

void BuaList::updateTop(){
    double maxValue = DBL_MIN;
    int maxID = 0;
    double secondMax = DBL_MIN;
    for (int i = 0; i < top.size(); i++){
        if (top[i].second.first > maxValue) {
            maxID = i;
            secondMax = maxValue;
            maxValue = top[i].second.first;
        }
    }
    pair<PointOnEdge, pair<double, double >> deleteItem = top[maxID];

    top.erase(top.begin() + maxID); // update top

    kthDistance = secondMax; // update kth distance

    vector<pair<PointOnEdge, pair<double, double >>> newCandidates; // update candidates
    for(auto candidate: candidates){
        if (candidate.second.second < kthDistance){
            newCandidates.push_back(candidate);
        }
    }

    if (deleteItem.second.second < kthDistance) newCandidates.push_back(deleteItem);

    candidates = newCandidates;
}

void BuaList::updateByInserting(PointOnEdge movingObject, double aggregateValue, double lowBound){ // assume the old point has been removed
    if (aggregateValue < kthDistance){
        top.push_back(
                pair<PointOnEdge, pair<double, double >>(movingObject,
                                                         pair<double, double >(aggregateValue, lowBound)));
        updateTop();
    }else if (lowBound < kthDistance){
        candidates.push_back(
                pair<PointOnEdge, pair<double, double >>(movingObject,
                                                         pair<double, double >(aggregateValue, lowBound)));
    }
}



void BuaList::updateByDeleting(PointOnEdge movingObject){ // assume the old point has been removed

    int pos1 = positionInCandidates(movingObject);
    if (pos1 != -1){
        candidates.erase(candidates.begin() + pos1);
    }
    int pos2 = positionInTop(movingObject);
    if (pos2 != -1){
        candidates.erase(candidates.begin() + pos2);
    }
    updateTop();
}

void BuaList::forwardUpdate(){
    while (where() != -1 && currentLowBound() <= kthDistance){
        auto movingObjects = currentOnEdgePoints();
        for (auto movingObject: movingObjects){
            updateByInserting(movingObject.first, movingObject.second.first, movingObject.second.second);
        }
        next();
    }
}

void BuaList::backwardUpdate(){
    last();
    while (currentLowBound() > kthDistance){
        auto movingObjects = currentOnEdgePoints();
        for (auto movingObject: movingObjects){
            updateByDeleting(movingObject.first);
        }
        last();
    }
    next();
}

bool BuaList::inTop(PointOnEdge movingObject){
    for (auto topObject: top){
        if (topObject.first.getID() == movingObject.getID()) return true;
    }
    return false;
}


bool BuaList::inCandidates(PointOnEdge movingObject){
    for (auto candidateObject: candidates){
        if (candidateObject.first.getID() == movingObject.getID()) return true;
    }
    return false;
}



int BuaList::positionInTop(PointOnEdge movingObject){
    for (int i = 0; i < top.size(); i++){
        if(top[i].first.getID() == movingObject.getID()) return i;
    }
    return -1;
}

int BuaList::positionInCandidates(PointOnEdge movingObject){
    for (int i = 0; i < top.size(); i++){
        if(candidates[i].first.getID() == movingObject.getID()) return i;
    }
    return -1;
}


void BuaList::bua(vector<PointOnEdge> deleteMovingObjects, vector<PointOnEdge> insertMovingObjects) {
    for (auto movingObject: deleteMovingObjects){
        updateByDeleting(movingObject);
        updateTop();
    }

    for (auto movingObject: insertMovingObjects){
        auto complexEdge = (ComplexEdge*) graph->getEdgeByID(movingObject.getEdgeID());
        auto aggregateValue = complexEdge->calculateAggregateWithDistEdges(movingObject.getPosition());
        auto queryEdge = complexEdge->getQueryEdge(movingObject);
        updateByInserting(movingObject, aggregateValue, queryEdge->lowBound());
        updateTop();
    }

    if (currentLowBound() <= kthDistance){
        forwardUpdate();
    } else{
        backwardUpdate();
    }
}
