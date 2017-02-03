/**
 * Determines attitude of the quadcopter using sensors and filters
 */
#include "AttitudeDeterminator.h"

/**
 * Instantiates sensors and filter
 */
AttitudeDeterminator::AttitudeDeterminator(double K_GYRO){
  IMU* imu;
  imu = new IMU;
  accelerometer = new Accelerometer(imu);
  Serial.println("Acc created");
  gyroscope = new Gyroscope(imu);
  
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
  XYZ<double> acc = accelerometer->updateAndGetData();
  XYZ<double> gyro = gyroscope->updateAndGetData();
  
  *pitch = pitchFilter->filter(acc.y, gyro.y);
  *roll = 0;
  *yaw = 0;
}


