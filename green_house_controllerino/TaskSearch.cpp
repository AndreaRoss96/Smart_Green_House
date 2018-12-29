#include "TaskSearch.h"

TaskSearch::TaskSearch(Sensor *prox){
  this->timeElapsed = 0;
}
/*
  if(GLOBAL_CLASS.isSearching()){
  bool TaskSearch::updateAndCheckTime(int basePeriod){
    timeElapsed += basePeriod;
    return true;
  }else{
    return false;
  }
}*/
bool TaskSearch::updateAndCheckTime(int basePeriod){ return true; }

void TaskSearch::tick(){
  if(!GLOBAL_CLASS.isConnected() && prox.getValue() < GLOBAL_CLASS.getEngagementDist()){
    GLOBAL_CLASS.toggleConnection();
  }else{
    if (GLOBAL_CLASS.isConnected() && prox.getValue() > GLOBAL_CLASS.getEngagementDist()) {
      GLOBAL_CLASS.toggleConnection();
    }
  }
}
