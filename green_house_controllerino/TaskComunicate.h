#define __TASKCOMUNICATE__
#ifndef __TASKCOMUNICATE__

#include "Task.h"
#include "MsgService.h"
#include "MsgServiceBT.h"

class TaskComunicate: public Task{
  public:
    TaskComunicate(MsgServiceBT *msgSBT);
    bool updateAndCheckTime(int basePeriod);
    void tick();
  private:
    int timeElapsed;
    MsgServiceBT *msgSBT;
}

#endif
