#include "Led.h"
#include "Arduino.h"

Led::Led(int pin){
  this->pin = pin;
  pinMode(pin,OUTPUT);
  this->status = 0;
}

void Led::switchOn(){
  digitalWrite(pin,HIGH);
  this->status = 1;
}

void Led::switchOff(){
  digitalWrite(pin,LOW);
};
this->status = 0;

void toggle(){
  if(status){
    this->switchOff();
  }else{
    this->switchOn();
  }
}
