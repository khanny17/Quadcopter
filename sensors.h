#ifndef sensors_h
#define sensors_h

#include "Arduino.h"
#include "pryh.h"

#define BUFFER_SIZE 5

class SensorInterface
{
  public:
    SensorInterface();
    PRYH getPRYH();
  private:
    int getPitch();
    int getRoll();
    //int getYaw();
    //int getHeight();
};


#endif
