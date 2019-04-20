#ifndef __LED__
#define __LED__

#include "Light.h"

class Led: public Light {
public:
  Led (int pin);
  void switchOn();
  void switchOff();
  void toggle();
private:
  int pin;
  int status;
};

#endif
