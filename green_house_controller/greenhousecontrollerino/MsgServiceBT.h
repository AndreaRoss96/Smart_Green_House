#ifndef __MSGSERVICEBT__
#define __MSGSERVICEBT__

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "MsgService.h"
// #include "SoftwareSerial.h"

/*Classe utilizzata per lo scambio di messaggi con il bluethoot 
attraverso la libreria SoftwareSerial, utilizza la classe Msg come pacchetto
per i messaggi*/

class MsgServiceBT {

public:
  MsgServiceBT(int rxPin, int txPin);
  void init();
  bool isMsgAvailable();
  Msg* receiveMsg();
  bool sendMsg(Msg msg);

private:
  String content;
  SoftwareSerial *channel;
};
#endif
