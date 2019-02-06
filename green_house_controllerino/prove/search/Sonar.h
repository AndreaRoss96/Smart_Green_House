#ifndef __SONAR__
#define __SONAR__

#include "Sensor.h"

class Sonar: public Sensor {
public:
  Sonar(int pinEcho, int pinTrig);
  float getValue();
private:
  int pinEcho;
  int pinTrig;
};

#endif
