#include "TaskComunicate.h"

TaskComunicate::TaskComunicate(MsgServiceBT *msgSBT, Light *la, Light *lm, ServoTimer2 *servo, LevelIndicator *lp){
  this->msgSBT = msgSBT;
  this->msgSBT->init();
  this->la=la;
  this->la->switchOn();
  this->lm=lm;
  this->lm->switchOff();
  this->servo=servo;
  this->lp=lp;
  this->lp->setLevel(map(GLOBAL_CLASS.getFlow(),0,100, MIN_LVL, MAX_LVL));
}
void TaskComunicate::init(int period){
  MsgService.init();

  Task::init(period);
}

void TaskComunicate::move(){
  this->lp->setLevel(map(GLOBAL_CLASS.getFlow(),0,100, MIN_LVL, MAX_LVL));
  this->servo->write(map(GLOBAL_CLASS.getFlow(),0,100, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH));
}

  /*Controlla la presenza di messaggi.
  * utilizza il seguente protocollo:
  * invio di messaggi:
  *   xx-a = xx umidità - modalità automatica
  *   xx-m = xx umidità - modalità manuale
  * ricezione messaggi:
  *   l = low (portata bassa)
  *   m = medium (portata media)
  *   h = high (portata alta)
  *   z = zero (portata nulla)
  *   Hxx = Humidity, xx indicata l'umidità nell'aria
  * invio messaggi al server:
  *   o = pompa aperta (open)
  *   c = pompa chiusa (portata nulla)
  *   0 = modalità automatica
  *   1 = modalità manuale
  */
void TaskComunicate::tick(){

  /*Controlla la presenza di messaggi sulla seriale.
  * sulla seriale e li considera solo nel caso il sistema sia in modalità
  * automatica, eccetto l'umidità che viene aggiornata sempre.
  */
  if(MsgService.isMsgAvailable()){
    Msg *a;
    a = MsgService.receiveMsg();
    String msg;
    msg = a->getContent();
    switch (msg[0]) {
      case 'l':{
        if(GLOBAL_CLASS.isAutoMode()){
          GLOBAL_CLASS.setFlow(LOWFLOW);
          this->move();
        }
        break;
      }
      case 'h':{
        if(GLOBAL_CLASS.isAutoMode()){
          GLOBAL_CLASS.setFlow(HIGHFLOW);
          this->move();
        }
        break;
      }
      case 'm':{
        if(GLOBAL_CLASS.isAutoMode()){
          GLOBAL_CLASS.setFlow(MEDIUMFLOW);
          this->move();
        }
        break;
      }
      case 'z':{
        if(GLOBAL_CLASS.isAutoMode()){
          GLOBAL_CLASS.setFlow(NOFLOW);
          this->move();
        }
        break;
      }
      case 'H':{
        int h = msg.substring(1).toInt();
        GLOBAL_CLASS.setHumidity(h);
        break;
      }
    }
    delete(a);
  }
  /*Controlla la presenza di messaggi sulla software seriale
  * e li considera solo nel caso il sistema sia connesso e in modalità manuale,
  * eccetto il messaggio di toggle della modalità.
  */
  if(GLOBAL_CLASS.isConnected()){
    if(msgSBT->isMsgAvailable()){
      Msg *a;
      a = msgSBT->receiveMsg();
      String msg = a->getContent();

      switch (msg[0]) {
        case 'l':{
          if(!GLOBAL_CLASS.isAutoMode()){
            GLOBAL_CLASS.setFlow(LOWFLOW);
            this->move();
            Serial.println("o");
          }
          break;
        }
        case 'h':{
          if(!GLOBAL_CLASS.isAutoMode()){
            GLOBAL_CLASS.setFlow(HIGHFLOW);
            this->move();
            Serial.println("o");
          }
          break;
        }
        case 'm':{
          if(!GLOBAL_CLASS.isAutoMode()){
            GLOBAL_CLASS.setFlow(MEDIUMFLOW);
              this->move();
              Serial.println("o");
          }
          break;
        }
        case 'z':{
          if(!GLOBAL_CLASS.isAutoMode()){
            GLOBAL_CLASS.setFlow(NOFLOW);
            this->move();
            Serial.println("c");
          }
          break;
        }
        case 't':{
          GLOBAL_CLASS.toggleAutomode();
          la->toggle();
          lm->toggle();
          Serial.println("" + GLOBAL_CLASS.isAutoMode() ? "0": "1");
          break;
        }
      }
      delete(a);
    }
    String cio = (String(GLOBAL_CLASS.getHumidity()) + "-");
    Msg *m = new Msg(cio + (GLOBAL_CLASS.isAutoMode() ? "a":"m"));
    msgSBT->sendMsg(m);
    delete(m);
  }
}
