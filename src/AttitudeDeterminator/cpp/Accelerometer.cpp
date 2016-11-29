/**
 * Subclass of IMUSensor that implements the Accelerometer
 */
#include "Accelerometer.h"

/**
 * Call super constructor with our constant values and zero sensor
 */
Accelerometer::Accelerometer(IMU* imu) : 
IMUSensor(imu, ADXL345_ADDRESS, ADXL_REGISTER_PWRCTL, ADXL_PWRCTL_MEASURE, ADXL345_REGISTER_XLSB){
  initSensor();
}

/**
 * Takes raw reading and converts it to degrees
 * Precondition: current values in data[] are not already in degrees
 */
void Accelerometer::convert(){
  float x = data[XAXIS];
  float y = data[YAXIS];
  float z = data[ZAXIS];
  
  //57.29578 is 180 / pi
  float xA = tan( x / sqrt( pow(y,2)+pow(z,2) ) )  * 57.296; 
  float yA = atan2( y , sqrt( pow(x,2)+pow(z,2) ) )  * 57.296;
  float zA = atan2( sqrt( pow(y,2)+pow(x,2) ) , z  )  * 57.296;
  
  data[XAXIS] = xA;
  data[YAXIS] = yA;
  data[ZAXIS] = zA;
}

