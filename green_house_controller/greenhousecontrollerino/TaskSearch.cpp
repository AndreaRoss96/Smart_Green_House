#include "TaskSearch.h"

TaskSearch::TaskSearch(Sensor *prox, Light *la, Light *lm){
  this->prox = prox;
  this->la=la;
  this->lm=lm;
}

void TaskSearch::init(int period){
  Task::init(period);
}

void TaskSearch::tick(){
  Serial.print("searching....");
  float a = this->prox->getValue();
  Serial.println(a);
  if(!GLOBAL_CLASS.isConnected() && a < GLOBAL_CLASS.getEngagementDist()){
    GLOBAL_CLASS.toggleConnection();
  }else{
    if(GLOBAL_CLASS.isConnected() && a > GLOBAL_CLASS.getEngagementDist()){
      GLOBAL_CLASS.toggleConnection();
      if(!GLOBAL_CLASS.isAutoMode()){
        GLOBAL_CLASS.toggleAutomode();
        this->la->switchOn();
        this->lm->switchOff();
      }
    }
  }
}
