#ifndef __TASKCLOSE__
#define __TASKCLOSE__

#include "Task.h"
#include "ServoTimer2.h"
#include "LevelIndicator.h"

class TaskClose: public Task{
  public:
    TaskClose(ServoTimer2 *servo, LevelIndicator *lp);
    void init(int period);
    bool updateAndCheckTime(int basePeriod);
    void tick();

  private:
    int timeElapsed;
    ServoTimer2 *servo;
    LevelIndicator *lp;
};

#endif
