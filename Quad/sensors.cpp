#include "Arduino.h"
#include "sensors.h"
#include "imu.h"
#include "buffer.h"
#include "ultrasonic.h"

imu imu;
Ultrasonic ultrasonic; //TODO config the pins?

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
 *  Updates sensor readings and returns the current PRY
 */
PRY SensorInterface::getPRY(){
  imu.update();
  ultrasonic.update();
  return (PRY){ this->getPitch(), this->getRoll(), 0 };
}

/**
 * Determines the current pitch of the quad using
 *   whichever sensors or combination of sensors would be most accurate
 *   i.e. If the quad is in motion, use the gyroscope instead of the accelerometer
 */
int SensorInterface::getPitch(){
  //Serial.println(imu.getAccData(Y));
  return imu.getAccData(Y); //TODO use the gyroscope
}

/**
 * Determines the current roll of the quad using
 *   whichever sensors or combination of sensors would be most accurate
 *   i.e. If the quad is in motion, use the gyroscope instead of the accelerometer
 */
//Buffers the Roll reading and returns the buffer average
int SensorInterface::getRoll(){
  return imu.getAccData(X); //TODO use the gyroscope
}

int SensorInterface::getHeight(){
  //eventually this function will decide to use the ultrasonic or the barometer based on the altitude
  return ultrasonic.getHeight();
}

/**
 * Returns the vertical velocity of the quad in centimeters per second
 */
int curTime, prevTime, velocity, prevHeight = 0;
int SensorInterface::getVerticalVelocity(){
  curTime = millis();
  velocity = (1000 * (this->getHeight() - prevHeight)) / (curTime - prevTime); //1000 * cm/ms)
  prevHeight = this->getHeight();
  prevTime = curTime;
  return velocity;
}


