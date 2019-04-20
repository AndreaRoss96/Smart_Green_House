#ifndef __FADINGLED__
#define __FADINGLED__

#include "Light.h"
#include "LevelIndicator.h"

/*fading led uses LevelIndicator as interface */

class FadingLed : public LevelIndicator{
public:
  FadingLed(int pin);
  void switchOn();
  void switchOff();
  void setLevel(int lvl);
  void toggle();
private:
  int pin;
  int status;
  int level;
};

#endif