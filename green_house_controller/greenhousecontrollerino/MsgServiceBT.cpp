#include "Arduino.h"
#include "MsgServiceBT.h"


MsgServiceBT::MsgServiceBT(int rxPin, int txPin){
   SoftwareSerial SWSerial (rxPin, txPin);
   this->channel = &SWSerial;
}

void MsgServiceBT::init(){
  content.reserve(256);
  this->channel->begin(9600);
}

bool MsgServiceBT::sendMsg(Msg msg){
  this->channel->print(msg.getContent());
}

bool MsgServiceBT::isMsgAvailable(){
  return this->channel->available();
}

Msg* MsgServiceBT::receiveMsg(){
  while (this->channel->available()) {
    char ch = (char) this->channel->read();
    if (ch == '\n'){
      Msg* msg = new Msg(content);
      content = "";
      return msg;
    } else {
      content += ch;
    }
  }
  return NULL;
}
