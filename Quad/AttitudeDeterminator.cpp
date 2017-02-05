/**
 * Determines attitude of the quadcopter using sensors and filters
 */
#include "AttitudeDeterminator.h"

/**
 * Instantiates sensors and filter
 */
AttitudeDeterminator::AttitudeDeterminator(double K_GYRO, Accelerometer *t_accelerometer, Gyroscope *t_gyroscope):
    accelerometer(t_accelerometer),
    gyroscope(t_gyroscope) {
  
    pitchFilter = new ComplimentaryFilter(K_GYRO);
    //pitchFilter = new KalmanFilter(1,1,1);
    //pitchFilter.init();
    rollFilter = new ComplimentaryFilter(K_GYRO);
    yawFilter = new ComplimentaryFilter(K_GYRO);
}

/**
 *  Fills passed pointers with their respective angle readings
 */
void AttitudeDeterminator::getAttitude(double* pitch, double* roll, double* yaw){
    accelerometer->update();
    gyroscope->update();
    XYZ<double> acc = accelerometer->getData();
    XYZ<double> gyro = gyroscope->getData();
    
    *pitch = pitchFilter->filter(acc.y, gyro.y);
    *roll = 0;
    *yaw = 0;
}


