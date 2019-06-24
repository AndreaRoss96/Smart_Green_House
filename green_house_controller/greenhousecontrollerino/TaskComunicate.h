#ifndef __TASKCOMUNICATE__
#define __TASKCOMUNICATE__

#include "Task.h"
#include "MsgService.h"
#include "MsgServiceBT.h"
#include "Light.h"
#include "ServoTimer2.h"
#include "LevelIndicator.h"

/*Task per la comunicazione tramite seriale e tramite bluetooth,
*  gestisce anche l'apertura e la chiusura in base ai messaggi che riceve
*/
class TaskComunicate: public Task{
  public:
    TaskComunicate(MsgServiceBT *msgSBT, Light *la, Light *lm, ServoTimer2 *servo, LevelIndicator *lp);
    void tick();
    void init(int period);

  private:
    void move();
    int timeElapsed;
    MsgServiceBT *msgSBT;
    Light *la, *lm;
    ServoTimer2 *servo;
    LevelIndicator *lp;
};

#endif
