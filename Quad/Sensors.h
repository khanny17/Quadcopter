#ifndef sensors_h
#define sensors_h

#include "Arduino.h"
#include "PRY.h"
#include "IMU.h"
#include "Buffer.h"
#include "Ultrasonic.h"
#include "Kalman.h"

#define P_VALUE  10000
#define Q_ANGLE .0005     
#define Q_BIAS  .004     
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
