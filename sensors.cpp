#include "Arduino.h"
#include "sensors.h"
#include "imu.h"
#include "buffer.h"

imu imu;

//TODO we probably want to buffer each individual sensor reading,
// instead of the pitch/roll/yaw/height value. This is in case we want to use the gyro
// and maybe we want a larger buffer for it.
Buffer<int> pitchBuffer(BUFFER_SIZE);  
Buffer<int> rollBuffer(BUFFER_SIZE);

SensorInterface::SensorInterface(){
  //imu.init(); For some reason, this was breaking it
}

/**
 *  Updates sensor readings and returns the current PRYH
 */
PRYH SensorInterface::getPRYH(){
  imu.update();
  return (PRYH){ this->getPitch(), this->getRoll(), 0, 0 };
}

//Buffers the Pitch reading and returns the buffer average
//This is to smooth the signal out
int SensorInterface::getPitch(){
  int* acc_data = imu.getAccData();
  pitchBuffer.add(acc_data[1]);//TODO put buffer in imu?
  return pitchBuffer.average();
}

//Buffers the Roll reading and returns the buffer average
int SensorInterface::getRoll(){
  int* acc_data = imu.getAccData();
  rollBuffer.add(acc_data[0]);
  return rollBuffer.average();
}
