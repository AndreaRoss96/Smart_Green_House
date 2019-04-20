#include "GlobalClass.h"
#include "Sensor.h"
#include "Sonar.h"
#include "Task.h"
#include "TaskSearch.h"
#include "Scheduler.h"

#define BAUD 9600
#define PINECHO 12
#define PINTRIG 13

Scheduler scheduler;

void setup() {
  Serial.begin(BAUD);
  Serial.flush();
  Sensor *prox = new Sonar(PINECHO, PINTRIG);
  Task *search = new TaskSearch(prox);
  search->init(100);//TODO find the time
  scheduler.init(50);//TODO find the time
  scheduler.addTask(search);

}

void loop(){
  scheduler.schedule();
}
