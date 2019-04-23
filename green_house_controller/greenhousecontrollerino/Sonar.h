#ifndef __SONAR__
#define __SONAR__

#include "Sensor.h"

/*Classe che implementa un Sonar estendo un sensore
NB delaymicroseconds non influisce con i timer*/
class Sonar: public Sensor {
public:
  Sonar(int pinEcho, int pinTrig);
  float getValue();
private:
  int pinEcho;
  int pinTrig;
};

#endif
