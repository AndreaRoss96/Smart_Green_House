#include "MsgServiceBT.h"
#include "Task.h"
#include "SoftwareSerial.h"
#include "TaskComunicate.h"
#include "TaskSearch.h"
#include "LevelIndicator.h"
#include "Led.h"
#include "Light.h"
#include "FadingLed.h"
#include "Sensor.h"
#include "Scheduler.h"
#include "ServoTimer2.h"
#include "Sonar.h"


#define BAUD 9600
#define PINECHO 12
#define PINTRIG 13
#define PINRX 10
#define PINTX 11
#define PINPORT 6
#define PINAUTO 8
#define PINMANU 7
#define PINSERVO 5

MsgServiceBT *msgServiceBT = new MsgServiceBT(PINRX,PINTX);

Scheduler scheduler;

void setup() {

  Serial.begin(BAUD);
  MsgService.init();
  msgServiceBT->init();
  Serial.flush();

  ServoTimer2 *servo = new ServoTimer2();
  servo->attach(PINSERVO);
  Sensor *prox = new Sonar(PINECHO, PINTRIG);
  Light *la = new Led(PINAUTO);
  la->toggle();
  Light *lm = new Led(PINMANU);
  LevelIndicator *lp = new FadingLed(PINPORT);
  servo->write(MIN_PULSE_WIDTH);
  lp->setLevel(MIN_LVL);

  Task *communicate = new TaskComunicate(msgServiceBT, la, lm, servo, lp);
  communicate->init(4);//TODO find the time
  Task *search = new TaskSearch(prox, la, lm);
  search->init(2);//TODO find the time


  scheduler.init(1);//TODO find the time
  scheduler.addTask(communicate);
  scheduler.addTask(search);
}

void loop(){
  scheduler.schedule();
}
