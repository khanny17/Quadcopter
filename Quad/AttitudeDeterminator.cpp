/**
 * Determines attitude of the quadcopter using sensors and filters
 */
#include "AttitudeDeterminator.h"

/**
 * Instantiates sensors and filter
 */
AttitudeDeterminator::AttitudeDeterminator(){
  IMU imu;
  
  Accelerometer acc(&imu);
  this->accelerometer = &acc;

  Gyroscope gyro(&imu);
  this->gyroscope = &gyro;
  
  ComplimentaryFilter p(K_GYRO);
  ComplimentaryFilter r(K_GYRO);
  ComplimentaryFilter y(K_GYRO);
  this->pitchFilter = &p;
  this->rollFilter = &r;
  this->yawFilter = &y;
}

/**
 *  Fills passed pointers with their respective angle readings
 */
void AttitudeDeterminator::getAttitude(float* pitch, float* roll, float* yaw){
  float accPitchReading, gyroPitchReading;
  accelerometer->getData(XAXIS, &accPitchReading);
  gyroscope->getData(XAXIS, &gyroPitchReading);
  
  *pitch = pitchFilter->filter(accPitchReading, gyroPitchReading);
  *roll = 0;
  *yaw = 0;
}


