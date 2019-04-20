#include "MsgService.h"

String content;

MsgServiceClass MsgService;

bool MsgServiceClass::isMsgAvailable(){
  return msgAvailable;
}

Msg* MsgServiceClass::receiveMsg(){
  if (msgAvailable){
    Msg* msg = currentMsg;
    msgAvailable = false;
    currentMsg = NULL;
    content = "";
    return msg;
  } else {
    return NULL;
  }
}

void MsgServiceClass::init(){
  content.reserve(256);
  content = "";
  currentMsg = NULL;
  msgAvailable = false;
}

void MsgServiceClass::sendMsg(const String& msg){
  Serial.println(msg);
  Serial.flush();
  delayMicroseconds(5000);
}

void serialEvent() {
  /* reading the content */
  while (Serial.available()) {
    char ch = (char) Serial.read();
    if (ch == '\n'){
      MsgService.currentMsg = new Msg(content);
      MsgService.msgAvailable = true;
    } else {
      content += ch;
    }
  }
}
