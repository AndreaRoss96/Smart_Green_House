#include "GlobalClass.h"
#include "Task.h"
#include "Scheduler.h"
#include "TaskOpen.h"
#include "TaskClose.h"
#include "TaskWait.h"
#include "LevelIndicator.h"
#include "ServoTimer2.h"
#include "Led.h"
#include "Light.h"
#include "FadingLed.h"

#define BAUD 9600
#define PINPORT 9
#define PINSERVO 5


Scheduler scheduler;

void setup() {

  Serial.begin(BAUD);
  Serial.flush();

  ServoTimer2 *servo = new ServoTimer2();
  servo->attach(PINSERVO);

  LevelIndicator *lp = new FadingLed(PINPORT);

  Task *open = new TaskOpen(servo, lp);
  open->init(50);//TODO find the time
  Task *close = new TaskClose(servo, lp);
  close->init(50);//TODO find the time
  Task *wait = new TaskWait();
  wait->init(50);//TODO find the time

  scheduler.init(25);//TODO find the time
  scheduler.addTask(open);
//  scheduler.addTask(close);
  scheduler.addTask(wait);


}

void loop(){
  scheduler.schedule();
}
