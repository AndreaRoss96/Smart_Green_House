#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Timer.h"
#include "Task.h"
#define MAX_TASKS 10

/*classe Scheduler utilizzata per far partire al momento giusto le funzioni del
sistema. Per ogni task inserito controlla che sia passato il tempo prefissato
prima di attivarlo*/
class Scheduler {

 int basePeriod;
 int nTasks;
 Task* taskList[MAX_TASKS];
 Timer timer;

public:
 void init(int basePeriod);
 virtual bool addTask(Task* Task);
 virtual void schedule();

};
#endif
