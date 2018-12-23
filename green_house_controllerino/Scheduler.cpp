#include "Scheduler.h"

void Scheduler::init(int basePeriod){
 this->basePeriod = basePeriod;
 timer.setupPeriod(basePeriod);
 nPhases = 0;
}

bool Scheduler::addPhase(Phase* phase){
  if (nPhases < MAX_TASKS-1){
    phaseList[nPhases] = phase;
    nPhases++;
    return true;
  } else {
    return false;
  }
}

void Scheduler::schedule(){
  timer.waitForNextTick();
  for (int i = 0; i < nPhases; i++){
    if (phaseList[i]->updateAndCheckTime(basePeriod)){
    phaseList[i]->tick();
    }
  }
}
