#ifndef __FADINGLED__
#define __FADINGLED__

#include "Light.h"
#include "LevelIndicator.h"

class FadingLed : public LevelIndicator, public Light
{
public:
  Led(int pin);
  void switchOn();
  void switchOff();
  void setLevel(int lvl);
  void toggle();
private:
  int pin;
  int status;
};

#endif
