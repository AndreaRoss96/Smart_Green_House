#include "TaskOpen.h"


TaskOpen::TaskOpen(ServoTimer2 *servo, LevelIndicator *lp){
  this->servo = servo;
  this->lp = lp;

}

TaskOpen::updateAndCheckTime(int basePeriod){
  if(GLOBAL_CLASS.isOpening()){
    Task::updateAndCheckTime(basePeriod);
  }else{
    return false;
  }
}

TaskOpen::init(int period){
  Task::init(period);
}

void TaskOpen::tick(){
  if(servo->read() != (int)map(GLOBAL_CLASS.getFlow(), 0, 100, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH)){
    this->servo->write((int)map(GLOBAL_CLASS.getFlow(), 0, 100, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH));
    this->lp->setLevel((int)map(GLOBAL_CLASS.getFlow(), 0, 100, MIN_LVL, MAX_LVL ));
  }else{
    GLOBAL_CLASS.done();
  }
}
