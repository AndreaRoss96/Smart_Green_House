#ifndef __TASKCOMUNICATE__
#define __TASKCOMUNICATE__

#include "Task.h"
#include "MsgService.h"
#include "MsgServiceBT.h"

class TaskComunicate: public Task{
  public:
    TaskComunicate(MsgServiceBT *msgSBT);
    void tick();
    void init(int period);

  private:
    int timeElapsed;
    MsgServiceBT *msgSBT;
    Light *la, *lm;
};

#endif
