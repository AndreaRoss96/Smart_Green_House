#include "TaskComunicate.h"
#include "Light.h"

TaskComunicate::TaskComunicate(MsgServiceBT *msgSBT, Light *la, Light *lm){
  this->msgSBT = msgSBT;
  this->la=la;
  this->lm=lm;
}

void TaskComunicate::init(int period){
  Task::init(period);
}

void TaskComunicate::tick(){
  String msg;
  while(MsgService.isMsgAvailable()){
    msg = MsgService.receiveMsg()->getContent();
    switch(msg[0]){
      case 'o': {//'o' = open the pump
        switch(msg[1]){
          case 'l': {
            GLOBAL_CLASS.setFlow(GLOBAL_CLASS.getlowflow());
            break;
          }
          case 'm': {
            GLOBAL_CLASS.setFlow(GLOBAL_CLASS.getmediumflow());
            break;
          }
          case 'h': {
            GLOBAL_CLASS.setFlow(GLOBAL_CLASS.gethighflow());
          break;
          }
        }
        if(GLOBAL_CLASS.isAutoMode())
          GLOBAL_CLASS.open();
        break;
      }
      case 'c':{//'c' = close pump
        if(GLOBAL_CLASS.isAutoMode())
          GLOBAL_CLASS.close();
        break;
      }
      case 'h':{//'h' = set humidity
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
        case 'o': {//'o' = open the pump
          if(!GLOBAL_CLASS.isAutoMode())
            switch(msg[1]){
              case 'l': {
                GLOBAL_CLASS.setFlow(GLOBAL_CLASS.getlowflow());
                break;
              }
              case 'm': {
                GLOBAL_CLASS.setFlow(GLOBAL_CLASS.getmediumflow());
                break;
              }
              case 'h': {
                GLOBAL_CLASS.setFlow(GLOBAL_CLASS.gethighflow());
              break;
              }
            }
            GLOBAL_CLASS.open();
          break;
        }
        case 'c':{//'c' = close pump
          if(!GLOBAL_CLASS.isAutoMode())
            GLOBAL_CLASS.close();
          break;
        }
        case 't':{//'t' = changes the mode
          GLOBAL_CLASS.toggleAutomode();
          la->toggle();
          lm->toggle();
          break;
        }
      }
    }
    Msg *m = new Msg("H"+GLOBAL_CLASS.getHumidity());
    msgSBT->sendMsg(*m);
  }
}
