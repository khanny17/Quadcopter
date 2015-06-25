#ifndef sensors_h
#define sensors_h

#include "Arduino.h"
#include "pryh.h"

class SensorInterface
{
  public:
    SensorInterface();
    PRYH getPRYH();
    void init();
  private:
    int getPitch();
    int getRoll();
    //int getYaw();
    int getHeight();
};


#endif
