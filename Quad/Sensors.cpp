#include "Sensors.h"

//Ultrasonic ultrasonic; //TODO config the pins?

/**
 * Performs any initialization necessary for the Sensors
 * NOTE: The initialization for some sensors, such as the imu,
 *         will not work if this is placed in the constructor,
 *         which is why this function exists.
 */
void SensorInterface::init(){
  //imu.init();
  //kalman.init(0,0,0,P_VALUE,P_VALUE);
}

/**
 *  Updates sensor readings and returns the current PRY
 */
void SensorInterface::getPRY(float* pitch, float* roll, float* yaw){
  //imu.update();
  //Serial.println(imu.getAccData(Y));
  //Serial.println(imu.getGyroData(Y));
  return;
}


