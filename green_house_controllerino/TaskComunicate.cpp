#include "TaskComunicate.h"
#include "Light.h"

TaskComunicate::TaskComunicate(MsgServiceBT *msgSBT, Light *la, Light *lm, ServoTimer2 *servo, LevelIndicator *lp){
  this->msgSBT = msgSBT;
  this->la=la;
  this->lm=lm;
  this->servo=servo;
  this->lp=lp;
}

void TaskComunicate::init(int period){
  Task::init(period);
}


void TaskComunicate::move(int flow){
    Serial.println("move!!!!");
    this->servo->write((int)map(flow, 0, 100, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH));
    this->lp->setLevel((int)map(flow, 0, 100, MIN_LVL, MAX_LVL));
}


void TaskComunicate::tick(){
  String msg;
  Serial.println("communicate");
  while(MsgService.isMsgAvailable()){
    msg = MsgService.receiveMsg()->getContent();
    switch(msg[0]){
      case 'l': {
        if(GLOBAL_CLASS.isAutoMode()){
          this->move(LOWFLOW);

        }
        break;
      }
      case 'm': {
        if(GLOBAL_CLASS.isAutoMode()){
          this->move(MEDIUMFLOW);
        }
        break;
      }
      case 'h': {
        if(GLOBAL_CLASS.isAutoMode()){
          this->move(HIGHFLOW);
        }
        break;
      }
      case 'z':{//'z' = close pump
        if(GLOBAL_CLASS.isAutoMode()){
          this->move(NOFLOW);

        }
        break;
      }
      case 'H':{//'H' = set humidity
        int h = msg.substring(1).toInt();
        GLOBAL_CLASS.setHumidity(h);

        break;
      }
    }
  }
  if(GLOBAL_CLASS.isConnected()){
    while(msgSBT->isMsgAvailable()){
      msg = msgSBT->receiveMsg()->getContent();
      switch(msg[0]){
        case 'l': {
          if(!GLOBAL_CLASS.isAutoMode())
            this->move(LOWFLOW);

            Serial.println("low");

          break;
        }
        case 'm': {
          if(!GLOBAL_CLASS.isAutoMode())
            this->move(MEDIUMFLOW);
          Serial.println("medium");

          break;
        }
        case 'h': {
          if(!GLOBAL_CLASS.isAutoMode())
            this->move(HIGHFLOW);

            Serial.println("high");
          break;
        }
        case 'z':{//'z' = close pump
          if(!GLOBAL_CLASS.isAutoMode())
            this->move(NOFLOW);

            Serial.println("no");
            break;
        }
        case 't':{//'t' = changes the mode
          GLOBAL_CLASS.toggleAutomode();
          Serial.println("toggle");
          la->toggle();
          lm->toggle();
          break;
        }
      }
    }
    String s;
    s.concat( GLOBAL_CLASS.getHumidity());
    s.concat("-");
    s.concat( (GLOBAL_CLASS.isAutoMode() ? "a" : "m"));
    Serial.print("messaggio inviato: ");
    Serial.println(s);
    Msg *m = new Msg(s);
    msgSBT->sendMsg(*m);
  }
}
