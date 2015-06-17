#include "Arduino.h"
#include "sensors.h"
#include "imu.h"
#include "buffer.h"

imu imu;

Buffer<int> pitchBuffer(BUFFER_SIZE);
Buffer<int> rollBuffer(BUFFER_SIZE);

SensorInterface::SensorInterface(){
  //imu.init();
}

PRYH SensorInterface::getPRYH(){
  imu.update();
  return (PRYH){ this->getPitch(), this->getRoll(), 0, 0 };
}

int SensorInterface::getPitch(){
  int* acc_data = imu.getAccData();
  pitchBuffer.add(acc_data[1]);//TODO put buffer in imu?
  return pitchBuffer.average();
}

int SensorInterface::getRoll(){
  int* acc_data = imu.getAccData();
  rollBuffer.add(acc_data[0]);
  return rollBuffer.average();
}
