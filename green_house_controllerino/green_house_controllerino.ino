#include "MsgServiceBT.h"
#include "Task.h"
#include "SoftwareSerial.h"
#include "TaskOpen.h"
#include "TaskClose.h"
#include "TaskComunicate.h"
#include "TaskSearch.h"
#include "TaskWait.h"
#include "LevelIndicator.h"
#include "Led.h"
#include "Light.h"
#include "FadingLed.h"
#include "Sensor.h"
#include "ServoTimer2.h"
#include "Sonar.h"


#define BAUD 9600
#define PINECHO 12
#define PINTRIG 13
#define PINRX 10
#define PINTX 11
#define PINPORT 9
#define PINAUTO 8
#define PINMANU 7
#define PINSERVO 5

MsgServiceBT *msgServiceBT = new MsgServiceBT(PINRX,PINTX);

Scheduler scheduler;

void setup() {

  Serial.begin(BAUD);
  MsgService.init();
  MsgServiceBT.init();
  Serial.flush();

  ServoTimer2 *servo = new ServoTimer2();
  servo->attach(PINSERVO);
  Sensor *prox = new Sonar(PINECHO, PINTRIG);
  Light *la = new Led(PINAUTO);
  Light *lm = new Led(PINMANU);
  LevelIndicator *lp = new FadingLed(PINPORT);

  Task *open = new TaskOpen(servo, lp);
  open->init(50);//TODO find the time
  Task *close = new TaskClose(servo, lp);
  close->init(150);//TODO find the time
  Task *wait = new TaskWait();
  wait->init(250);//TODO find the time
  Task *communicate = new TaskComunicate(msgServiceBT);
  communicate->init(100);//TODO find the time
  Task *search = new TaskSearch(prox);
  search->init(50);//TODO find the time


  scheduler.init(50);//TODO find the time
  scheduler.addTask(open);
  scheduler.addTask(close);
  scheduler.addTask(wait);
  scheduler.addTask(communicate);
  scheduler.addTask(search);
}

void loop(){
  scheduler.schedule();
}
