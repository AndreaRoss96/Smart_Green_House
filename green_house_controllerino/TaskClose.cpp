#include "TaskClose.h"

TaskClose::TaskClose(ServoTimer2 *servo, LevelIndicator *lp){
  this->servo = servo;
  this->lp = lp;
}

TaskClose::init(int period){
  Task::init(period);
}

TaskClose::updateAndCheckTime(int basePeriod){
  if(GLOBAL_CLASS.isClosing()){
    Task::updateAndCheckTime(basePeriod);
  }else{
    return false;
  }
}

void TaskClose::tick(){
  if(servo->read() != map(0, 0, 100, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH)){
    servo->write(map(0, 0, 100, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH));
    lp->setLevel(map(0, 0, 100, MIN_LVL, MAX_LVL));
  }else{
    GLOBAL_CLASS.done();
  }
}
