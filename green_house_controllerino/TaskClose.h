#ifndef __TASKCLOSE__
#define __TASKCLOSE__

#include "Task.h"
#include "ServoTimer2.h"
#include "LevelIndicator.h"

class TaskClose: public Task{
  public:
    TaskClose(ServoTimer2 *servo, LevelIndicator *lp);
    bool updateAndCheckTime(int basePeriod);
    void tick();
    void init(int period);

  private:
    int timeElapsed;
    ServoTimer2 *servo;
    LevelIndicator *lp;
};

#endif
