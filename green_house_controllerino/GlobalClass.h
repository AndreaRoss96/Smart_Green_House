#include "EnumPhase.h"
#include "Arduino.h"

#define DIST  0.3
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

    int getEngagementDist(){
      return DIST;
    }

    void setFlow(int f){ flow = f; }
    void setHumidity(int h){ humidity = h; }
    void toggleAutomode(){ automatic = !automatic; }
    void toggleConnection(){ connected = !connected; }


    int getFlow(){ return flow;  }
    int getHumidity(){ return humidity;  }
    bool isAutoMode(){ return automatic;  }
    bool isConnected(){ return connected;  }
/*
    bool isSearching(){ return searcing; }
    void connectionFound(){ searcing = false; connected = true; }

    bool isConnected(){ return connected; }
    void connectionLost(){ searcing = true; connected = false; }
*/
    bool isWaiting(){ return wait; }
    void done(){ opening = false; closing = false; wait = true; }

    bool isOpening(){ return opening; }
    void open(){ opening = true; closing = false; wait = false; }

    bool isClosing(){ return closing; }
    void close(){ opening = false; closing = true; wait = false; }
};
