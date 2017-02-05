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
    static const double ACC_LPF_ALPHA = 0.5;
    
    AttitudeDeterminator(double K_GYRO, Accelerometer *t_accelerometer, Gyroscope *t_gyroscope);
    void getAttitude(double* pitch, double* roll, double* yaw); //fills passed pointers with angle values
  private:
    Accelerometer *accelerometer;
    Gyroscope *gyroscope;
    Filter* pitchFilter;
    Filter* rollFilter;
    Filter* yawFilter;
};


#endif
