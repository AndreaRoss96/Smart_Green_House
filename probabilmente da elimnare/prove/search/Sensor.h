#ifndef __SENSOR__
#define __SENSOR__

#include "Arduino.h"

class Sensor {
public:
  virtual float getValue() = 0;
};

#endif
