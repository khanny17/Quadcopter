/**
 * Determines attitude of the quadcopter using sensors and filters
 */
#ifndef AttitudeDeterminator_h
#define AttitudeDeterminator_h

#include "Accelerometer.h"
#include "Gyroscope.h"
#include "Filter.h"
#include "KalmanFilter.h"
#include "ComplimentaryFilter.h"


class AttitudeDeterminator
{
  public:
    AttitudeDeterminator(float K_GYRO);
    void getAttitude(float* pitch, float* roll, float* yaw); //fills passed pointers with angle values
  private:
    IMUSensor* accelerometer;
    IMUSensor* gyroscope;
    Filter* pitchFilter;
    Filter* rollFilter;
    Filter* yawFilter;
};


#endif
