#ifndef __LEVELINDICATOR__
#define __LEVELINDICATOR__

#define MAX_LVL 255
#define MIN_LVL 0

/* This inerface represents a level indicator where you can set the level beetwen
a MAX_LVL and a MIN_LVL*/

class LevelIndicator {
public:
  virtual void setLevel(int level) = 0;

private:
  int level;
};
#endif
