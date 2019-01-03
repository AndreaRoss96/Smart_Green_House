#include "FadingLed.h"
#include "Arduino.h"

FadingLed::Led(int pin){
  this->pin = pin;
  pinMode(pin,OUTPUT);
  status = 0;
}

void FadingLed::switchOn(){
  digitalWrite(pin,HIGH);
  status = 1;
  brightness = MAX_BRIG;
}

void FadingLed::switchOff(){
  digitalWrite(pin,LOW);
  status = 0;
  brightness = MIN_BRIG;
};

void FadingLed::toggle(){
  if(status){
    this.switchOff();
  }else{
    this.switchOn();
  }
}

void FadingLed::setBrightness(int brightness){
  if(brightness < MAX_BRIG && brightness > MIN_BRIG){
    this->brightness = brightness;
    analogWrite(this->pin, this, brightness)
  }
}
