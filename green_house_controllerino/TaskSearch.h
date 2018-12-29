#define __TASKSEARCH__
#ifndef __TASKSEARCH__

#include "Task.h"
#include "Sensor.h"

class TaskSearch: public Task{
  public:
    TaskSearch(Sensor *prox);
    bool updateAndCheckTime(int basePeriod);
    void tick();
  private:
    Sensor *prox;
    bool connected = false;
    int timeElapsed;
}

#endif
