#ifndef sensors_h
#define sensors_h

#include "Arduino.h"
#include "PRY.h"
#include "IMU.h"
#include "Buffer.h"
#include "Ultrasonic.h"
#include "Kalman.h"

class SensorInterface
{
  public:
    SensorInterface(float K_gP);
    PRY getPRY();
    void init();
    int getHeight();
    int getVerticalVelocity();
    void testImu();
  private:
    KalmanFilter kalman(1,1,1);
    float getPitch();
    float getRoll();
    //float getYaw();
    unsigned long pitch_t_prev;
    float pitch;
    //Values used to change the impact of each of the sensors
    //(K_gyro_pitch is a float from 0-1 controlling the significance of the gyro vs the accelerometer)
    float K_gyro_pitch;
    float K_acc_pitch; //(1-K_gyro_pitch) No sense making that calculation every cycle
};


#endif
