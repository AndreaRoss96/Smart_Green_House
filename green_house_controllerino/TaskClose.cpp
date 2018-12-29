#include "TaskClose.h"

TaskClose::TaskClose(/*TODO servomotore*/){
  this->timeElapsed = 0;
}

bool TaskClose::updateAndCheckTime(int basePeriod){
  if(GLOBAL_CLASS.isClosing()){
    timeElapsed += basePeriod;
    return true;
  }else{
    return false;
  }
}

void TaskClose::tick(){
  /*aziona il servomotore in base al timeElapsed*/
}
