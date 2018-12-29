#define __TASKWAIT__
#ifndef __TASKWAIT__

#include "Task.h"

class TaskWait: public Task{
  public:
    TaskWait();
    bool updateAndCheckTime(int basePeriod);
    void tick();
  private:
    int timeElapsed;
}

#endif
