#ifndef __LEVELINDICATOR__
#define __LEVELINDICATOR__

#define MAX_LVL 255
#define MIN_LVL 0

class LevelIndicator {
public:
  virtual void setLevel() = 0;

private:
  int level;
};
#endif
