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

/*used to move a servo.
it need a number from 0 to 100 */
void TaskComunicate::move(int flow){
    Serial.println("move!!!!");
    this->servo->write((int)map(flow, 0, 100, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH));
    this->lp->setLevel((int)map(flow, 0, 100, MIN_LVL, MAX_LVL));
}


void TaskComunicate::tick(){
  String msg;
  Serial.println("communicate");
  while(MsgService.isMsgAvailable()){
    msg = MsgService.receiveMsg()->getContent();
    Serial.println("messaggio da serial " + msg);
    switch(msg[0]){
      case 'l': {
        if(GLOBAL_CLASS.isAutoMode()){
          this->move(LOWFLOW);

        }
        break;
      }
      case 'm': {
        if(GLOBAL_CLASS.isAutoMode()){
          this->move(MEDIUMFLOW);
        }
        break;
      }
      case 'h': {
        if(GLOBAL_CLASS.isAutoMode()){
          this->move(HIGHFLOW);
        }
        break;
      }
      case 'z':{//'z' = close pump
        if(GLOBAL_CLASS.isAutoMode()){
          this->move(NOFLOW);

        }
        break;
      }
      case 'H':{//'H' = set humidity
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
        case 'l': {
          if(!GLOBAL_CLASS.isAutoMode())
            this->move(LOWFLOW);

            Serial.println("low");

          break;
        }
        case 'm': {
          if(!GLOBAL_CLASS.isAutoMode())
            this->move(MEDIUMFLOW);
          Serial.println("medium");

          break;
        }
        case 'h': {
          if(!GLOBAL_CLASS.isAutoMode())
            this->move(HIGHFLOW);

            Serial.println("high");
          break;
        }
        case 'z':{//'z' = close pump
          if(!GLOBAL_CLASS.isAutoMode())
            this->move(NOFLOW);

            Serial.println("no");
            break;
        }
        case 't':{//'t' = changes the mode
          GLOBAL_CLASS.toggleAutomode();
          Serial.println("toggle");
          la->toggle();
          lm->toggle();
          break;
        }
      }
    }
    this->s = "";
    this->s.concat( GLOBAL_CLASS.getHumidity());
    this->s.concat("-");
    if(GLOBAL_CLASS.isAutoMode() ){
      this->s.concat("a");
    }else{
      this->s.concat("m");
    }

    Serial.print("messaggio inviato: ");
    Serial.println(s);
    Msg *m = new Msg(s);
    msgSBT->sendMsg(*m);
  }
}

/* la funzione tick() è divisa in due sezioni principali:
la prima controlla i messaggi sulla seriale, a seconda del loro significato e
dello stato del sistema possono venire interpretati o meno
la seconda controlla i messaggi sul canale bluetooth se è presente una connessione.
A seconda del loro significato e dello stato del sistema possono venire
interpretati o meno.
sempre se è presente una connessione invia sul canale bluetooth un messaggio
contenente percentuale di umidità e lo stato del sistema

di seguito il protocollo che abbiamo utilizzato:
h     - sets high flow
m     - sets medium flow
l     - sets low flow
z     - sets zero flow (close the pump)
Hxx   - sets the humidity as xx
t     - toggle the control mode
xx-y  - sends the humidity and a if automatic mode or b if manual pinMode   */
