/**
 * Determines attitude of the quadcopter using sensors and filters
 */
#include "AttitudeDeterminator.h"

/**
 * Instantiates sensors and filter
 */
AttitudeDeterminator::AttitudeDeterminator(){
  IMU* imu;
  imu = new IMU;
  accelerometer = new Accelerometer(imu);
  gyroscope = new Gyroscope(imu);
  
  pitchFilter = new ComplimentaryFilter(K_GYRO);
  rollFilter = new ComplimentaryFilter(K_GYRO);
  yawFilter = new ComplimentaryFilter(K_GYRO);
}

/**
 *  Fills passed pointers with their respective angle readings
 */
void AttitudeDeterminator::getAttitude(float* pitch, float* roll, float* yaw){
  Serial.println("Getting Attitude");
  float accPitchReading, gyroPitchReading;
  accelerometer->getData(YAXIS, &accPitchReading);
  Serial.println("Getting Gyro");
  gyroscope->getData(YAXIS, &gyroPitchReading);
  Serial.println("Got Gyro");
  *pitch = pitchFilter->filter(accPitchReading, gyroPitchReading);
  *roll = 0;
  *yaw = 0;
}


