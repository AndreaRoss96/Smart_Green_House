#include "Sonar.h"

const float vs = 331.5 + 0.6*20;

Sonar::Sonar(int pinEcho, int pinTrig){
  this->pinEcho = pinEcho;
  this->pinTrig = pinTrig;
  pinMode(pinTrig,OUTPUT);
  pinMode(pinEcho,INPUT);
}

float Sonar::getValue(){
  digitalWrite(pinTrig,LOW);
  delayMicroseconds(3);
  digitalWrite(pinTrig,HIGH);
  delayMicroseconds(5);
  digitalWrite(pinTrig,LOW);

  /* ricevi l’eco */
  float tUS = pulseIn(pinEcho, HIGH);
  float t = tUS / 1000.0 / 1000.0 / 2;
  float d = t*vs;
  return d;
};
