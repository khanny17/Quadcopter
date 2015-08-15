/**
 * Abstract class to define standard methods for each sensor on the IMU board
 * 
 * Originally adapted from: http://robotosh.blogspot.com/2012/03/sparkfun-9dof-imu-sensor-stick.html
 */
#include "IMUSensor.h"

/**
 * Constructs a new IMUSensor object, saving the passed values and initializing other member variables
 */
IMUSensor::IMUSensor(IMU* imu, int address, byte initRegister, byte i2cWriteData, byte readRegister){
  this->imu = imu;
  this->address = address;
  this->initRegister = initRegister;
  this->i2cWriteData = i2cWriteData;
  this->readRegister = readRegister;
  data[XAXIS] = 0;
  data[YAXIS] = 0;
  data[ZAXIS] = 0;
}

/**
 * Puts sensor reading for a given axis into the passed "data" pointer.
 * Returns: true if successfully executed
 *          false if invalid axis given
 */
bool IMUSensor::getData(int axis, float* data){
  if(axis == XAXIS || axis == YAXIS || axis == ZAXIS){
    *data = this->data[axis];
    return true;
  } else {
    return false;
  }
}

/**
 * Talks to IMU and initializes sensor
 */
void IMUSensor::initSensor(){
  byte data = 0;
  imu->i2cWrite(address, initRegister, i2cWriteData);
  imu->i2cRead(address, initRegister, 1, &data);
}

/**
 * Reads new data from the IMU
 */
void IMUSensor::readSensor(){
  byte bytes[6];
  memset(bytes, 0, 6);

  imu->i2cRead(address, readRegister, 6, bytes);

  for (int i = 0; i < 3; ++i) {
   this->data[i] = (int)bytes[2*i] + (((int)bytes[2*i + 1]) << 8);
 }
}

