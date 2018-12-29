#ifndef __TASKOPEN__
#define __TASKOPEN__

#include "Task.h"
#include "ServoTimer2.h"


class TaskOpen: public Task{
  public:
    TaskOpen(/*TODO servomotore*/);
    bool updateAndCheckTime(int basePeriod);
    void tick();
  private:
    int timeElapsed;
    ServoTimer2 servo;

}

#endif
