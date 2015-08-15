#ifndef sensors_h
#define sensors_h

#include "Arduino.h"
#include "IMU.h"
#include "Buffer.h"
#include "Ultrasonic.h"

#define P_VALUE  10000
#define Q_ANGLE .0005     
#define Q_BIAS  .004     
#define R       .03

class SensorInterface
{
  public:
    void getPRY(float* pitch, float* roll, float* yaw);
    void init();
};


#endif
