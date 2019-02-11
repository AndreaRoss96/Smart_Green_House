#ifndef __GLOBALCLASS__
#define __GLOBALCLASS__

#include "Arduino.h"

#define DIST  0.3
#define NOFLOW 0
#define LOWFLOW 20
#define MEDIUMFLOW 50
#define HIGHFLOW 100
/*
#define
#define
#define
#define
...... TODO*/


class GlobalClass { //SINGLETON


  private:
      GlobalClass() {}

      bool automatic = true;
      int flow = 0;
      int humidity = 0;
      bool connected = false;

      bool searching = true;
      bool wait = true;
      bool opening = false;
      bool closing = false;


  public:
    /*
    return
      The instance of the globalClass
    */
    static GlobalClass& getInstance() {
        static GlobalClass gbInstance;
        return gbInstance;
    }

    float getEngagementDist(){
      return DIST;
    }

    void setFlow(int f){ flow = f; }
    void setHumidity(int h){ humidity = h; }
    void toggleAutomode(){ automatic = !automatic;}
    void toggleConnection(){ connected = !connected; }


    int getFlow(){ return flow;  }
    int getHumidity(){ return humidity;  }
    bool isAutoMode(){ return automatic;  }
    bool isConnected(){ return connected;  }



};
#endif
