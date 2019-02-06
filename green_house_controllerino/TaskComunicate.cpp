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

void move(){
  if(servo->read() != (int)map(GLOBAL_CLASS.getFlow(), 0, 100, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH)){
    this->servo->write((int)map(GLOBAL_CLASS.getFlow(), 0, 100, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH));
    this->lp->setLevel((int)map(GLOBAL_CLASS.getFlow(), 0, 100, MIN_LVL, MAX_LVL ));
  }
}

void TaskComunicate::tick(){
  String msg;
  while(MsgService.isMsgAvailable()){
    msg = MsgService.receiveMsg()->getContent();
    switch(msg[0]){
      case 'l': {
        if(GLOBAL_CLASS.isAutoMode()){
          GLOBAL_CLASS.setFlow(GLOBAL_CLASS.getlowflow());
        }
        break;
      }
      case 'm': {
        if(GLOBAL_CLASS.isAutoMode()){
          GLOBAL_CLASS.setFlow(GLOBAL_CLASS.getmediumflow());
        }
        break;
      }
      case 'h': {
        if(GLOBAL_CLASS.isAutoMode()){
          GLOBAL_CLASS.setFlow(GLOBAL_CLASS.gethighflow());
        }
        break;
      }
      case 'z':{//'z' = close pump
        if(GLOBAL_CLASS.isAutoMode()){
          GLOBAL_CLASS.setFlow(GLOBAL_CLASS.getNoflow());
        }
        break;
      }
      case 'h':{//'h' = set humidity
        int h = msg.substring(1).toInt();
        GLOBAL_CLASS.setHumidity(h);
        break;
      }
      this->move();
    }
  }
  if(GLOBAL_CLASS.isConnected()){
    while(msgSBT->isMsgAvailable()){
      msg = msgSBT->receiveMsg()->getContent();
      switch(msg[0]){
        case 'l': {
          if(!GLOBAL_CLASS.isAutoMode())
            GLOBAL_CLASS.setFlow(GLOBAL_CLASS.getlowflow());
          break;
        }
        case 'm': {
          if(!GLOBAL_CLASS.isAutoMode())
            GLOBAL_CLASS.setFlow(GLOBAL_CLASS.getmediumflow());
          break;
        }
        case 'h': {
          if(!GLOBAL_CLASS.isAutoMode())
            GLOBAL_CLASS.setFlow(GLOBAL_CLASS.gethighflow());
          break;
        }
        case 'z':{//'z' = close pump
          if(!GLOBAL_CLASS.isAutoMode())
          GLOBAL_CLASS.setFlow(GLOBAL_CLASS.getNoflow());
          break;
        }
        case 't':{//'t' = changes the mode
          GLOBAL_CLASS.toggleAutomode();
          la->toggle();
          lm->toggle();
          break;
        }
      }
      this->move();
    }
    Msg *m = new Msg("" + GLOBAL_CLASS.getHumidity());
    msgSBT->sendMsg(*m);
  }
}
