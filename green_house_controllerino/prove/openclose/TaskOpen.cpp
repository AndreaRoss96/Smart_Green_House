#include "TaskOpen.h"


TaskOpen::TaskOpen(ServoTimer2 *servo, LevelIndicator *lp){
  this->servo = servo;
  this->lp = lp;
}

bool TaskOpen::updateAndCheckTime(int basePeriod){
  Serial.println("_______do i ever reach this point?_______" );

  if(GLOBAL_CLASS.isOpening() == true){
    Serial.println(":::::::can OPEN go?:::::::" );
    Serial.println(GLOBAL_CLASS.isOpening());
    Task::updateAndCheckTime(basePeriod);
  }else{
    Serial.println("Do i ever get in here?");
    basePeriod = 0;
    return false;
  }
}

void TaskOpen::init(int period){
  Task::init(period);
}

void TaskOpen::tick(){
  Serial.println((int)map(GLOBAL_CLASS.getFlow(), 0, 100, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH));
  Serial.println(servo->read());
  if(servo->read() != (int)map(GLOBAL_CLASS.getFlow(), 0, 100, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH)){
    Serial.println("open");
    servo->write((int)map(GLOBAL_CLASS.getFlow(), 0, 100, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH));
    lp->setLevel((int)map(GLOBAL_CLASS.getFlow(), 0, 100, MIN_LVL, MAX_LVL ));
  }else{
    Serial.println("else open");
    GLOBAL_CLASS.done();
  }
}
