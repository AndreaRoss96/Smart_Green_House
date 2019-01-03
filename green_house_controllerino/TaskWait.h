#ifndef __TASKWAIT__
#define __TASKWAIT__

#include "Task.h"

class TaskWait: public Task{
  public:
    TaskWait();
    void tick();
    void init(int period);

  private:
    int timeElapsed;
};

#endif
