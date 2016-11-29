#include "ComplimentaryFilter.h"

ComplimentaryFilter::ComplimentaryFilter(float K_gyro){
  if(K_gyro > 1 || K_gyro < 0){
    Serial.println("WARNING: invalid value for K_gyro");
  }
  this->K_gyro = K_gyro;
  this->K_acc = 1-K_gyro;
  prevTime = 0;
  pitch = 0;
}

float ComplimentaryFilter::filter(float accReading, float gyroReading){
  float gyro, acc;
  bufferValues(accReading, gyroReading, &acc, &gyro);
  
  if(prevTime == 0){ //We dont want a huge reading the first time we do it
    prevTime = millis();
  }
  //Integrate gyro reading:
  float dt = (float)(millis()-prevTime)/1000;
  float G = gyro*dt + pitch;
  
  prevTime = millis(); //save time for next cycle
  pitch = K_gyro * G + K_acc * acc; //save pitch
  
  return pitch;
}

void ComplimentaryFilter::bufferValues(float accReading, float gyroReading, float* acc, float* gyro){
  accBuffer.add(accReading);
  gyroBuffer.add(gyroReading);
  *acc = accBuffer.average();
  *gyro = gyroBuffer.average();
}
