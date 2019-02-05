#include "Scheduler.h"

void Scheduler::init(int basePeriod){
 this->basePeriod = basePeriod;
 timer.setupPeriod(basePeriod);
 nTasks = 0;
}

bool Scheduler::addTask(Task* task){
  if (nTasks < MAX_TASKS-1){
    taskList[nTasks] = task;
    nTasks++;
    return true;
  } else {
    return false;
  }
}

void Scheduler::schedule(){
  timer.waitForNextTick();
  Serial.println("schedule");
  for (int i = 0; i < nTasks; i++){
    bool r = taskList[i]->updateAndCheckTime(basePeriod);
    Serial.println(r);
    if (r){
      taskList[i]->tick();
    }
  }
}
