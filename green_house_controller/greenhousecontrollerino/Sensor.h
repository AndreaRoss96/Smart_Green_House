#ifndef __SENSOR__
#define __SENSOR__

#include "Arduino.h"

/*Interfaccia di un sensore che restituide un singolo valore float*/

class Sensor {
public:
  virtual float getValue() = 0;
};

#endif
