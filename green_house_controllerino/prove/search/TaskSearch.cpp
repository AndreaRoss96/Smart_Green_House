#include "TaskSearch.h"

TaskSearch::TaskSearch(Sensor *prox){
  this->prox = prox;
}

void TaskSearch::init(int period){
    Task::init(period);
    this->connected = GLOBAL_CLASS.isConnected();
}

//TODO look if you can understand how the bt connetion works
void TaskSearch::tick(){
  int a = prox->getValue();
  if(!GLOBAL_CLASS.isConnected() &&  a < GLOBAL_CLASS.getEngagementDist()){
    GLOBAL_CLASS.toggleConnection();
    Serial.println("connection toogled because distance is");
    Serial.println(prox->getValue() );

  }else{
    if (GLOBAL_CLASS.isConnected() && a > GLOBAL_CLASS.getEngagementDist()) {
      GLOBAL_CLASS.toggleConnection();
      Serial.println("connection toogled because distance is");
      Serial.println(prox->getValue() );
    }
  }
}
