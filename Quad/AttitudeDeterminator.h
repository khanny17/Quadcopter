/**
 * Determines attitude of the quadcopter using sensors and filters
 */
#ifndef AttitudeDeterminator_h
#define AttitudeDeterminator_h

#include "Arduino.h"
#include "Accelerometer.h"
#include "Gyroscope.h"

class AttitudeDeterminator
{
  public:
    AttitudeDeterminator();
    void getAttitude(float* pitch, float* roll, float* yaw); //fills passed pointers with angle values
  private:
    Accelerometer* accelerometer;
    Gyroscope* gyroscope;
};


#endif
