#include "TaskWait.h"

TaskWait::TaskWait(){
  this->timeElapsed = 0;
}

bool TaskWait::updateAndCheckTime(int basePeriod){
  if(GLOBAL_CLASS.isWaiting()){
    timeElapsed += basePeriod;
    return true;
  }else{
    return false;
  }
}

void TaskWait::tick(){

}
