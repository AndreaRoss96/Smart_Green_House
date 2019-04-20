#ifndef __TASK__
#define __TASK__

#define GLOBAL_CLASS GlobalClass::getInstance()

#include "GlobalClass.h"
#include "Arduino.h"

/* a generic task, implements init() and updateAndCheckTime() as they have most likely
always the same behaviour*/

class Task {
  int myPeriod;
  int timeElapsed;
public:
  virtual void init(int period){
    myPeriod = period;
    timeElapsed = 0;
  }

  virtual bool updateAndCheckTime(int basePeriod){
    timeElapsed += basePeriod;
    if (timeElapsed >= myPeriod){
      timeElapsed = 0;
      return true;
    } else {
      return false;
    }
  }

  virtual void tick() = 0;
};

#endif
