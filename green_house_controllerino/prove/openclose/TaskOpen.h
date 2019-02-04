#ifndef __TASKOPEN__
#define __TASKOPEN__

#include "Task.h"
#include "ServoTimer2.h"
#include "LevelIndicator.h"


class TaskOpen: public Task{
  public:
    TaskOpen(ServoTimer2 *servo, LevelIndicator *lp);
    void tick();
    void init(int period);
    bool updateAndCheckTime(int basePeriod);

  private:
    int timeElapsed;
    ServoTimer2 *servo;
    LevelIndicator *lp;
};

#endif
