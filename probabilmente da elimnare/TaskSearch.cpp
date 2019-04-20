#include "TaskSearch.h"

TaskSearch::TaskSearch(Sensor *prox, Light *la, Light *lm){
  this->prox = prox;
  this->la=la;
  this->lm=lm;
}

void TaskSearch::init(int period){
    Task::init(period);

    /*TODO probably useless*/
    this->connected = GLOBAL_CLASS.isConnected();
}

/*search for something in the engagement zone and sets the connection in response*/

void TaskSearch::tick(){
  Serial.print("search:   dist = ");
  int a = prox->getValue();
  Serial.println(a);
  if(!GLOBAL_CLASS.isConnected() &&  a < GLOBAL_CLASS.getEngagementDist()){
    GLOBAL_CLASS.toggleConnection();
  }else{
    if (GLOBAL_CLASS.isConnected() && a > GLOBAL_CLASS.getEngagementDist()) {
      GLOBAL_CLASS.toggleConnection();
      if(!GLOBAL_CLASS.isAutoMode()){
        GLOBAL_CLASS.toggleAutomode();
        this->la->switchOn();
        this->lm->switchOff();
      }
    }
  }
}

/* ricerca una presenza entro la distanza di approccio e nel caso la trovi attiva
la connessione, nel caso la perda la disattiva e setta la modalità ad automatica*/
