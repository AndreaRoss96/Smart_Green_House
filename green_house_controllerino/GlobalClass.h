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
  EnumTask actualTask = EnumTask.WAIT;//TODO
  bool automatic = true;

  private:
      GlobalClass() {}

      bool searcing;
      bool connected;
      bool wait;
      bool opening;
      bool closing;
      

  public:
    /*
    return
      The instance of the globalClass
    */
    static GlobalClass& getInstance() {
        static GlobalClass gbInstance;
        return gbInstance;
    }

    /*
    Set the actual Task
    */
    void setActualTask(EnumTask task) {
      this->actualTask = task;
    }

    /*
    return
      the actual Task
    */
    EnumPhase getActualTask() {
      return actualTask;
    }

    int getEngagementDist(){
      return DIST;
    }
    //int get.... TODO

    int isAutoMode(){
      return automatic;
    }
};
