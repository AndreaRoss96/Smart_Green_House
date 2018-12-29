#ifndef __TASKCLOSE__
#define __TASKCLOSE__

#include "Task.h"
#include "ServoTimer2.h"

class TaskClose: public Task{
  public:
    TaskClose(/*TODO servomotore*/);
    bool updateAndCheckTime(int basePeriod);
    void tick();
  private:
    int timeElapsed;
}

#endif
