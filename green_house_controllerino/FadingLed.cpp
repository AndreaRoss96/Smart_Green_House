#include "FadingLed.h"
#include "Arduino.h"

FadingLed::FadingLed(int pin){
  this->pin = pin;
  analogWrite(this->pin, this->level);
  status = 0;
}

void FadingLed::switchOn(){
  level = MAX_LVL;

  analogWrite(this->pin, this->level);
  status = 1;
}

void FadingLed::switchOff(){
  level = MIN_LVL;
  digitalWrite(pin,LOW);
  status = 0;
}

void FadingLed::toggle(){
  if(status){
    this->switchOff();
  }else{
    this->switchOn();
  }
}

void FadingLed::setLevel(int level){
  // if(level <= MAX_LVL && level >= MIN_LVL){
  Serial.println("level fled = ");
  Serial.println(level);
    this->level = level;
    analogWrite(this->pin, this->level);
  // }
}
