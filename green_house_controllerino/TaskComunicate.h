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
    void move(int flow);
    int timeElapsed;
    MsgServiceBT *msgSBT;
    Light *la, *lm;
    ServoTimer2 *servo;
    LevelIndicator *lp;
    String s;
};

#endif
