#ifndef sensors_h
#define sensors_h

#include "Arduino.h"
#include "pry.h"

class SensorInterface
{
  public:
    SensorInterface();
    PRY getPRY();
    void init();
    int getHeight();
    int getVerticalVelocity();
  private:
    int getPitch();
    int getRoll();
    //int getYaw();
};


#endif
