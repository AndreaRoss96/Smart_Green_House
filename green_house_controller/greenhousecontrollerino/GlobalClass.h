#ifndef __GLOBALCLASS__
#define __GLOBALCLASS__

#include "Arduino.h"

#define DIST  0.3
#define NOFLOW 0
#define LOWFLOW 20
#define MEDIUMFLOW 50
#define HIGHFLOW 100
/*
global class that stores the state of the machine as well as the various constant
*/


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


/*classe globale che contiene lo stato del sistema e le varie costanti che verranno
utilizzate lungo tutto il codice, implementa un singleton*/
