/**
 * Determines attitude of the quadcopter using sensors and filters
 */
#ifndef AttitudeDeterminator_h
#define AttitudeDeterminator_h

#include "Arduino.h"
#include "Accelerometer.h"
#include "Gyroscope.h"
#include "Filter.h"
#include "ComplimentaryFilter.h"

#define K_GYRO .5 //value for the complimentary filter - should this be defined here, or passed to the constructor?

class AttitudeDeterminator
{
  public:
    AttitudeDeterminator();
    void getAttitude(float* pitch, float* roll, float* yaw); //fills passed pointers with angle values
  private:
    Accelerometer* accelerometer;
    Gyroscope* gyroscope;
    Filter* pitchFilter;
    Filter* rollFilter;
    Filter* yawFilter;
};


#endif
