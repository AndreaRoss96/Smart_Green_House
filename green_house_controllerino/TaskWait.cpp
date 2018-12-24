#include "TaskWait.h"

TaskWait::TaskWait(){
  this->timeElapsed = 0;
}

bool TaskWait::updateAndCheckTime(int basePeriod){
  if(GLOBAL_CLASS.getActualTask() == EnumTask::WAIT)
    timeElapsed += basePeriod;
    return true;
  }else{
    return false;
  }
}

void TaskWait::tick(){
  /*if(GLOBAL_CLASS.getOpen()){
    GLOBAL_CLASS.setActualTask = EnumTask.OPENPUMP;
    return;
  }
  if(GLOBAL_CLASS.getClose()){
    GLOBAL_CLASS.setActualTask = EnumTask.CLOSEPUMP;
    return;
  }*/
  //guarda il prof
  
}
