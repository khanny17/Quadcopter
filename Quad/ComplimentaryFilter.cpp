#include "ComplimentaryFilter.h"

ComplimentaryFilter::ComplimentaryFilter(double K_gyro){
  if(K_gyro > 1 || K_gyro < 0){
    Serial.println("WARNING: invalid value for K_gyro");
  }
  this->K_gyro = K_gyro;
  this->K_acc = 1-K_gyro;
  prevTime = 0;
  angle = 0;
}

double ComplimentaryFilter::filter(double accData, double gyroData){
    if(prevTime == 0){ //We dont want a huge reading the first time we do it
        prevTime = millis();
    }
    //Integrate gyro reading:
    double dt = (double)(millis()-prevTime)/1000;
    double gyroIntegrated = gyroData*dt + angle;
    
    prevTime = millis(); //save time for next cycle
    angle = K_gyro * gyroIntegrated + K_acc * accData; //save pitch
    
    return angle;
}
