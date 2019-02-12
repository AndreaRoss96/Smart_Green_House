#ifndef __SONAR__
#define __SONAR__

#include "Sensor.h"

/*the class to operate a sonar, implements Sensor
NB delaymicroseconds doesn't create problems with timer*/
class Sonar: public Sensor {
public:
  Sonar(int pinEcho, int pinTrig);
  float getValue();
private:
  int pinEcho;
  int pinTrig;
};

#endif
