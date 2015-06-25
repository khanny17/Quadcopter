#include "Arduino.h"
#include "sensors.h"
#include "imu.h"
#include "buffer.h"
#include "ultrasonic.h"

imu imu;
Ultrasonic ultrasonic(7); //TODO config this

//TODO does this need to be here at all?
SensorInterface::SensorInterface(){
  //imu.init();
}

/**
 * Performs any initialization necessary for the Sensors
 * NOTE: The initialization for some sensors, such as the imu,
 *         will not work if this is placed in the constructor,
 *         which is why this function exists.
 */
void SensorInterface::init(){
  imu.init();
}

/**
 *  Updates sensor readings and returns the current PRYH
 */
PRYH SensorInterface::getPRYH(){
  imu.update();
  //imu.prettyPrint();
  return (PRYH){ this->getPitch(), this->getRoll(), 0, this->getHeight() };
}

/**
 * Determines the current pitch of the quad using
 *   whichever sensors or combination of sensors would be most accurate
 *   i.e. If the quad is in motion, use the gyroscope instead of the accelerometer
 */
int SensorInterface::getPitch(){
  return imu.getAccData(Y);
}

//Buffers the Roll reading and returns the buffer average
int SensorInterface::getRoll(){
  return imu.getAccData(X);
}

int SensorInterface::getHeight(){
  //eventually this function will decide to use the ultrasonic or the barometer from the pi
  return ultrasonic.getHeight();
}
