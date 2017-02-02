/**
 * Determines attitude of the quadcopter using sensors and filters
 */
#ifndef AttitudeDeterminator_h
#define AttitudeDeterminator_h

#include "Arduino.h"
#include "Accelerometer.h"
#include "Gyroscope.h"
#include "Filter.h"
#include "KalmanFilter.h"
#include "ComplimentaryFilter.h"


class AttitudeDeterminator
{
  public:
    AttitudeDeterminator(double K_GYRO);
    boolean getAttitude(double* pitch, double* roll, double* yaw); //fills passed pointers with angle values
  private:
    IMUSensor* accelerometer;
    IMUSensor* gyroscope;
    Filter* pitchFilter;
    Filter* rollFilter;
    Filter* yawFilter;
};


#endif
