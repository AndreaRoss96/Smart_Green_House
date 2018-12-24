#include "MsgServiceBT.h"
#include "SoftwareSerial.h"

#define BAUD 9600

MsgServiceBT msgServiceBT(2,3);

Scheduler scheduler;

void setup() {
  Serial.begin(BAUD);
  MsgService.init();
  MsgServiceBT.init();
  Serial.flush();

  // BT init
  /* set the name to green*/



  scheduler.init();//TODO find the time
  scheduler.addPhase();//TODO add all phases
}

void loop(){
  scheduler.schedule();

}
