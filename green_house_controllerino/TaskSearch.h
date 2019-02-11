#ifndef __TASKSEARCH__
#define __TASKSEARCH__

#include "Task.h"
#include "Sensor.h"
#include "Light.h"

class TaskSearch: public Task{
  public:
    TaskSearch(Sensor *prox, Light *la, Light *lm);
    void tick();
    void init(int period);

  private:
    Light *la, *lm;
    Sensor *prox;
    bool connected;
    int timeElapsed;
};

#endif
