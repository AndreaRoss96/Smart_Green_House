#define __TASKWAIT__
#ifndef __TASKWAIT__

#include "Task.h"
#include "MsgService.h"
#include "MsgServiceBT.h"

class TaskWait: public Task{
  public:
    TaskWait();
    bool updateAndCheckTime(int basePeriod);
    void tick();
  private:
    int timeElapsed;
}
