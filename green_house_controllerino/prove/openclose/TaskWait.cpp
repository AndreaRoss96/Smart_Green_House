#include "TaskWait.h"

TaskWait::TaskWait(){
}

bool TaskWait::updateAndCheckTime(int basePeriod){
  if(GLOBAL_CLASS.isWaiting()){
    Task::updateAndCheckTime(basePeriod);
  }else{
    basePeriod = 0;
    return false;
  }
}

void TaskWait::init(int period){
  temp = 100;
  Task::init(period);
}

void TaskWait::tick(){
  Serial.println(temp);
  GLOBAL_CLASS.setFlow(temp);
  if(temp != 0){
//    GLOBAL_CLASS.open();
    temp = 0;
  }else{
//    GLOBAL_CLASS.close();
    temp = 100;
  }
}
