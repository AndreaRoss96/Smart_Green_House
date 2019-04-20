#include "FadingLed.h"
#include "Arduino.h"

FadingLed::FadingLed(int pin){
  this->pin = pin;
  pinMode(pin,OUTPUT);
  status = 0;
}

void FadingLed::switchOn(){
  digitalWrite(pin,HIGH);
  status = 1;
  level = MAX_LVL;
}

void FadingLed::switchOff(){
  digitalWrite(pin,LOW);
  status = 0;
  level = MIN_LVL;
};

void FadingLed::toggle(){
  if(status){
    this->switchOff();
  }else{
    this->switchOn();
  }
}

void FadingLed::setLevel(int level){
  if(level <= MAX_LVL && level >= MIN_LVL){
    this->level = level;
    analogWrite(this->pin, this->level);
  }
}
