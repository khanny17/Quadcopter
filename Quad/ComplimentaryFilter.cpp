#include "ComplimentaryFilter.h"

ComplimentaryFilter::ComplimentaryFilter(double K_gyro){
  if(K_gyro > 1 || K_gyro < 0){
    Serial.println("WARNING: invalid value for K_gyro");
  }
  this->K_gyro = K_gyro;
  this->K_acc = 1-K_gyro;
  prevTime = 0;
  pitch = 0;
}

double ComplimentaryFilter::filter(double accReading, double gyroReading){
  double gyro, acc;
  bufferValues(accReading, gyroReading, &acc, &gyro);
  
  if(prevTime == 0){ //We dont want a huge reading the first time we do it
    prevTime = millis();
  }
  //Integrate gyro reading:
  double dt = (double)(millis()-prevTime)/1000;
  double G = gyro*dt + pitch;

  //Lets Low pass filter the gyro reading
  if((gyro*dt) <  10){
     G = pitch; //If its too low, assume nothing has changed
  }
  
  prevTime = millis(); //save time for next cycle
  pitch = K_gyro * G + K_acc * acc; //save pitch
  
  return pitch;
}

void ComplimentaryFilter::bufferValues(double accReading, double gyroReading, double* acc, double* gyro){
  accBuffer.add(accReading);
  gyroBuffer.add(gyroReading);
  *acc = accBuffer.average();
  *gyro = gyroBuffer.average();
}
