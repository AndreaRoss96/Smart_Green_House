#ifndef __TASKSEARCH__
#define __TASKSEARCH__

#include "Task.h"
#include "Sensor.h"

class TaskSearch: public Task{
  public:
    TaskSearch(Sensor *prox);
    void tick();
    void init(int period);

  private:
    Sensor *prox;
    bool connected;
    int timeElapsed;
};

#endif
