#ifndef sensors_h
#define sensors_h

#include "Arduino.h"
#include "PRY.h"
#include "IMU.h"
#include "Buffer.h"
#include "Ultrasonic.h"
#include "Kalman.h"

#define P_VALUE 10000 //High because not initializing
#define Q_ANGLE .001     
#define Q_BIAS  .003     
#define R       .03

class SensorInterface
{
  public:
    PRY getPRY();
    void init();
  private:
    KalmanFilter kalman{Q_ANGLE,Q_BIAS,R};
};


#endif
