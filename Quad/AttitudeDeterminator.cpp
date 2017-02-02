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
boolean AttitudeDeterminator::getAttitude(double* pitch, double* roll, double* yaw){
  double accPitchReading, gyroPitchReading;
  boolean accSuccess = accelerometer->getData(YAXIS, &accPitchReading);
  boolean gyroSuccess = gyroscope->getData(YAXIS, &gyroPitchReading);
  
  *pitch = pitchFilter->filter(accPitchReading, gyroPitchReading);
  *roll = 0;
  *yaw = 0;

  return accSuccess && gyroSuccess;
}


