#include "TaskOpen.h"


TaskOpen::TaskOpen(ServoTimer2 servo){
  this->timeElapsed = 0;
}

bool TaskOpen::updateAndCheckTime(int basePeriod){
  if(GLOBAL_CLASS.isOpening()){
    timeElapsed += basePeriod;
    return true;
  }else{
    return false;
  }
}

void TaskOpen::tick(){
}
