#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Timer.h"
#include "Phase.h"
#define MAX_TASKS 10

class Scheduler {

 int basePeriod;
 int nPhases;
 Phase* phaseList[MAX_TASKS];
 Timer timer;

public:
 void init(int basePeriod);
 virtual bool addPhase(Phase* phase);
 virtual void schedule();

};
#endif
