#include "MsgServiceBT.h"
#include "Task.h"
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

#define PINRX 4
#define PINTX 5

#define PINPORT 6
#define PINAUTO 8
#define PINMANU 7
#define PINSERVO 2

Scheduler scheduler;

/*
Parte principale del programma, inizializza i vari componenti e li fa interagire
*/

void setup(){
  Serial.begin(BAUD);
  Serial.flush();

  pinMode(PINRX,INPUT);
  pinMode(PINTX,OUTPUT);
  pinMode(PINPORT,OUTPUT);
  pinMode(PINAUTO,OUTPUT);
  pinMode(PINMANU,OUTPUT);
  pinMode(PINSERVO,OUTPUT);

  ServoTimer2 *servo = new ServoTimer2();
  Sensor *prox = new Sonar(PINECHO, PINTRIG);
  Light *la = new Led(PINAUTO);
  Light *lm = new Led(PINMANU);
  LevelIndicator *lp = new FadingLed(PINPORT);

  MsgServiceBT *msgServiceBT = new MsgServiceBT(PINRX, PINTX);
  MsgService.init();
  servo->attach(PINSERVO);
  servo->write(MIN_PULSE_WIDTH);
  lp->setLevel(MIN_LVL);

  Task *search = new TaskSearch(prox, la, lm);
  Task *comunicate = new TaskComunicate(msgServiceBT, la, lm, servo, lp);

  comunicate->init(100);
  search->init(500);
  scheduler.init(250);
  scheduler.addTask(comunicate);
  scheduler.addTask(search);
}

void loop (){
  scheduler.schedule();
}
