#ifndef __LED__
#define __LED__

#include "Light.h"
/* led class implements the Light interface*/

class Led: public Light {
public:
  Led(int pin);
  void switchOn();
  void switchOff();
  void toggle();
private:
  int pin;
  int status;
};

#endif
