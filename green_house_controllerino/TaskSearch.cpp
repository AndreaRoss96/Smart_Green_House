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
  if(!GLOBAL_CLASS.isConnected() && prox.getValue() < GLOBAL_CLASS.getEngagementDist()){
    GLOBAL_CLASS.toggleConnection();
  }else{
    if (GLOBAL_CLASS.isConnected() && prox.getValue() > GLOBAL_CLASS.getEngagementDist()) {
      GLOBAL_CLASS.toggleConnection();
    }
  }
}
