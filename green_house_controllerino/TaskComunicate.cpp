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
  while(MsgService.isMsgAvailable()){
    msg = MsgService.receiveMsg().getContent();
    switch(msg[0]){
      case 'o': {//'o' = open the pump
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
        msg.erase(0,1);
        int h = std::stoi(msg);
        GLOBAL_CLASS.setHumidity(h);
        break;
      }
    }
  }
  if(GLOBAL_CLASS.isConnected()){
    while(msgSBT.isMsgAvailable()){
      msg = msgSBT.receiveMsg().getContent();
      switch(msg[0]){
        case 'o': {//'o' = open the pump
          if(!GLOBAL_CLASS.isAutoMode())
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
          La->toggle();
          lm->toggle();
          break;
        }
      }
    }
    msgSBT.sendMsg("H"+GLOBAL_CLASS.getHumidity);
  }
}
