#ifndef __TASKCOMUNICATE__
#define __TASKCOMUNICATE__

#include "Task.h"
#include "MsgService.h"
#include "MsgServiceBT.h"
#include "Light.h"
#include "ServoTimer2.h"
#include "LevelIndicator.h"

class TaskComunicate: public Task{
  public:
    TaskComunicate(MsgServiceBT *msgSBT, Light *la, Light *lm, ServoTimer2 *servo, LevelIndicator *lp);
    void tick();
    void init(int period);

  private:
    int timeElapsed;
    MsgServiceBT *msgSBT;
    Light *la, *lm;
    void move(int flow);
    ServoTimer2 *servo;
    LevelIndicator *lp;
};

#endif
