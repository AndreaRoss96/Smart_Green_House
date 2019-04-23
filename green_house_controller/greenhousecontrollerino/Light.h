#ifndef __LIGHT__
#define __LIGHT__

/* Interfaccia light classica */

class Light {
public:
  virtual void switchOn() = 0;
  virtual void switchOff() = 0;
  virtual void toggle() = 0;
};

#endif
