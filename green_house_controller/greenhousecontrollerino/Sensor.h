#ifndef __SENSOR__
#define __SENSOR__

#include "Arduino.h"

/* a generic Sensor that can return a single value */

class Sensor {
public:
  virtual float getValue() = 0;
};

#endif
