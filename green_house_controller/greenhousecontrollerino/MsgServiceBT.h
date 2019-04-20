#ifndef __MSGSERVICEBT__
#define __MSGSERVICEBT__

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "MsgService.h"
// #include "SoftwareSerial.h"

/* Message service throught BT using AltSoftSerial on timer 1*/

class MsgServiceBT {

public:
  MsgServiceBT(int rxPin, int txPin);
  void init();
  bool isMsgAvailable();
  Msg* receiveMsg();
  bool sendMsg(Msg msg);

private:
  String content;
  // AltSoftSerial altSoftSerial;
  // AltSoftSerial *channel;
  SoftwareSerial *channel;
  // SoftwareSerial *channel;
};
/*l'utilizzo del timer uno è derivato dall'uso degli altri due timer per
servomotore (timer 2) e scheduler (timer 0).
non viene utilizzata la SoftwareSerial perchè creava problemi con il blocco degli interrupt
NB altsoftware serial utilizza di default i pin 8 e 9 e disabilita il pin 10 vedi l'internet
*/

/*this declaration already exist in another class*/
/*
class Msg {
  String content;

public:
  Msg(const String& content){
    this->content = content;
  }

  String getContent(){
    return content;
  }
};*/
#endif
