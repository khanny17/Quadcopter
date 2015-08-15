#include "ComplimentaryFilter.h"

ComplimentaryFilter::ComplimentaryFilter(float K_gyro){
  if(K_gyro > 1 || K_gyro < 0){
    Serial.println("WARNING: invalid value for K_gyro");
  }
  this->K_gyro = K_gyro;
  this->K_acc = 1-K_gyro;
}

float ComplimentaryFilter::filter(float accReading, float gyroReading){
  return K_gyro * gyroReading + K_acc + accReading;
}
