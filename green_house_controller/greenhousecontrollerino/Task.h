#ifndef __TASK__
#define __TASK__

#define GLOBAL_CLASS GlobalClass::getInstance()

#include "GlobalClass.h"
#include "Arduino.h"

/*Classe che definisce un Task generico, implementandone le funzioni init() e
updateAndCheckTime() in quanto questa avranno verosimilmente sempre lo stesso
comportamento */

class Task {
  int myPeriod;
  int timeElapsed;
public:

  virtual void init(int period){
    myPeriod = period;
    timeElapsed = 0;
  }

  /*controlla se il tempo passato è maggiore di quello da aspettare
    parameter:
      basePeriod tempo passato dall'ultima invocazione del metodo
    return:
      true se il tempo passato è maggiore del periodo di attivazione del Task
      false se il tempo non è sufficiente 
    */
  virtual bool updateAndCheckTime(int basePeriod){
    timeElapsed += basePeriod;
    if (timeElapsed >= myPeriod){
      timeElapsed = 0;
      return true;
    } else {
      return false;
    }
  }

  virtual void tick() = 0;
};

#endif
