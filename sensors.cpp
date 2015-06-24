#include "Arduino.h"
#include "sensors.h"
#include "imu.h"
#include "buffer.h"
#include "ultrasonic.h"

imu imu;
Ultrasonic ultrasonic(7); //TODO config this

//TODO we probably want to buffer each individual sensor reading
Buffer<int> pitchBuffer(BUFFER_SIZE);  
Buffer<int> rollBuffer(BUFFER_SIZE);

SensorInterface::SensorInterface(){
  //imu.init();
}

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

//Buffers the Pitch reading and returns the buffer average
//This is to smooth the signal out
int SensorInterface::getPitch(){
  int* acc_data = imu.getAccData();
  pitchBuffer.add(acc_data[1]);//TODO put buffer in imu or in here?
  return pitchBuffer.average();
}

//Buffers the Roll reading and returns the buffer average
int SensorInterface::getRoll(){
  int* acc_data = imu.getAccData();
  rollBuffer.add(acc_data[0]);
  return rollBuffer.average();
}

int SensorInterface::getHeight(){
  //eventually this function will decide to use the ultrasonic or the barometer from the pi
  return ultrasonic.getHeight();
}
