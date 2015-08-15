/**
 * Determines attitude of the quadcopter using sensors and filters
 */
#include "AttitudeDeterminator.h"

/**
 * Performs any initialization necessary for the Sensors
 * NOTE: The initialization for some sensors, such as the imu,
 *         will not work if this is placed in the constructor,
 *         which is why this function exists.
 */
void AttitudeDeterminator::init(){
  //imu.init();
  //kalman.init(0,0,0,P_VALUE,P_VALUE);
}

/**
 *  Updates sensor readings and returns the current PRY
 */
void AttitudeDeterminator::getPRY(float* pitch, float* roll, float* yaw){
  //imu.update();
  //Serial.println(imu.getAccData(Y));
  //Serial.println(imu.getGyroData(Y));
  return;
}


