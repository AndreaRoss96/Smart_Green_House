#include "TaskSearch.h"

TaskSearch::TaskSearch(Sensor *prox, Light *la, Light *lm){
  this->prox = prox;
  this->la=la;
  this->lm=lm;
}

void TaskSearch::init(int period){
    Task::init(period);
    this->connected = GLOBAL_CLASS.isConnected();
}

//TODO look if you can understand how the bt connetion works
void TaskSearch::tick(){
  Serial.println("search");
  int a = prox->getValue();
  if(!GLOBAL_CLASS.isConnected() &&  a < GLOBAL_CLASS.getEngagementDist()){
    GLOBAL_CLASS.toggleConnection();
    Serial.println("connection toogled because distance is");
    Serial.println(prox->getValue() );

  }else{
    if (GLOBAL_CLASS.isConnected() && a > GLOBAL_CLASS.getEngagementDist()) {
      GLOBAL_CLASS.toggleConnection();
      if(!GLOBAL_CLASS.isAutoMode()){
        GLOBAL_CLASS.toggleAutomode();
        this->la->switchOn();
        this->lm->switchOff();
      }
      Serial.println("connection toogled because distance is");
      Serial.println(prox->getValue() );
    }
  }
}
