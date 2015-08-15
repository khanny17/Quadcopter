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
}

/**
 *  Fills passed pointers with their respective angle readings
 */
void AttitudeDeterminator::getAttitude(float* pitch, float* roll, float* yaw){
  //TODO
}


