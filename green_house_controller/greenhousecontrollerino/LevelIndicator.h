#ifndef __LEVELINDICATOR__
#define __LEVELINDICATOR__

#define MAX_LVL 255
#define MIN_LVL 0

/* Interfaccia che rappresenta un indicatore di livello dove tra un
minimo (MIN_LVL) e un massimo (MAX_LVL)*/

class LevelIndicator {
public:
  virtual void setLevel(int level) = 0;

private:
  int level;
};
#endif
