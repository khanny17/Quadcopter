/**
 * Abstract class to define standard methods for each sensor on the IMU board
 * 
 * Originally adapted from: http://robotosh.blogspot.com/2012/03/sparkfun-9dof-imu-sensor-stick.html
 */
#include "IMUSensor.h"

/**
 * Constructs a new IMUSensor object, saving the passed values and initializing other member variables
 */
IMUSensor::IMUSensor(IMU* imu, int address, char initRegister, char i2cWriteData, char readRegister){
  this->imu = imu;
  this->address = address;
  this->initRegister = initRegister;
  this->i2cWriteData = i2cWriteData;
  this->readRegister = readRegister;
  //Set data and zero values to 0
  for(int i = 0; i < 3; ++i){
    data[i] = 0;
    zero[i] = 0;
  }
}

/**
 * Puts sensor reading for a given axis into the passed "data" pointer.
 * Returns: true if successfully executed
 *          false if invalid axis given
 */
bool IMUSensor::getData(int axis, float* data){
  readSensor();
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
  char data = 0;
  imu->i2cWrite(address, initRegister, i2cWriteData);
  //Use to check what we just wrote: imu->i2cRead(address, initRegister, 1, &data);
  findZero();
}

/**
 * Reads new data from the IMU
 */
void IMUSensor::readSensor(){
  char chars[6] = {};

  imu->i2cRead(address, readRegister, 6, chars);
  
  for (int i = 0; i < 3; ++i) {
    this->data[i] = (int)chars[2*i] + (((int)chars[2*i + 1]) << 8);
  }
  convert();
  zeroData();
}

/**
 * Zero the data based on our previous values for zero
 */
void IMUSensor::zeroData(){
  data[XAXIS] -= zero[XAXIS];
  data[YAXIS] -= zero[YAXIS];
  data[ZAXIS] -= zero[ZAXIS];
}

/**
 * Get sensor reading when quadcopter is perfectly flat and not moving and save as 0 value
 */
void IMUSensor::findZero(){
  float x = 0, y = 0, z = 0;
  for(int i = 0; i < ZERO_SAMPLE_COUNT; ++i){
    readSensor();
    x += data[XAXIS];
    y += data[YAXIS];
    z += data[ZAXIS];
    this_thread::sleep_for(chrono::milliseconds(10));
  }
  
  zero[XAXIS] = x/ZERO_SAMPLE_COUNT;
  zero[YAXIS] = y/ZERO_SAMPLE_COUNT;
  zero[ZAXIS] = z/ZERO_SAMPLE_COUNT;
}
