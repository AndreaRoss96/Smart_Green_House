#include "TaskWait.h"

TaskWait::TaskWait(){
}

bool TaskWait::updateAndCheckTime(int basePeriod){
  if(GLOBAL_CLASS.isWaiting()){
    Task::updateAndCheckTime(basePeriod);
  }else{
    return false;
  }
}

void TaskWait::init(int period){
  Task::init(period);
}

void TaskWait::tick(){

}
