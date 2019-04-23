#ifndef __LED__
#define __LED__

#include "Light.h"
/*Classe Led che implementa l'interfaccia Light*/

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
