#ifndef sensors_h
#define sensors_h

#include "Arduino.h"
#include "pry.h"

class SensorInterface
{
  public:
    SensorInterface();
    PRY getPRY();
    void init(float K_gP);
    int getHeight();
    int getVerticalVelocity();
  private:
    int getPitch();
    int getRoll();
    //int getYaw();
    int pitch_t_prev;
    int pitch;
    //Values used to change the impact of each of the sensors
    //(K_gyro_pitch is a float from 0-1 controlling the significance of the gyro vs the accelerometer)
    float K_gyro_pitch;
    float K_acc_pitch; //(1-K_gyro_pitch) No sense making that calculation every cycle
};


#endif
