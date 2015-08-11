#ifndef sensors_h
#define sensors_h

#include "Arduino.h"
#include "PRY.h"
#include "IMU.h"
#include "Buffer.h"
#include "Ultrasonic.h"
#include "Kalman.h"

#define P_VALUE 10000 //High because not initializing

class SensorInterface
{
  public:
    PRY getPRY();
    void init();
  private:
    KalmanFilter kalman{1,1,1};
};


#endif
