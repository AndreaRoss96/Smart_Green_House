#include "TaskComunicate.h"
#include <iostream>
#include <string>


TaskComunicate::TaskComunicate(MsgServiceBT *msgSBT){
  this->timeElapsed = 0;
  this->msgSBT = msgSBT;
}
/*
bool TaskComunicate::updateAndCheckTime(int basePeriod){
  if(GLOBAL_CLASS.isWaiting()){
    timeElapsed += basePeriod;
    return true;
  }else{
    return false;
  }
}*/
bool TaskComunicate::updateAndCheckTime(int basePeriod){ return true; }

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
          GLOBAL_CLASS.toggleAutomode(h);
          break;
        }
      }
    }
    msgSBT.sendMsg("H"+GLOBAL_CLASS.getHumidity);
  }
}
