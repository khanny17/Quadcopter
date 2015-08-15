/**
 * Subclass of IMUSensor that defines the Accelerometer
 */
#include "Accelerometer.h"

/**
 * Call super constructor with our constant values,
 *  zeroes sensor to just "0"
 */
Accelerometer::Accelerometer(IMU* imu) : 
IMUSensor(imu, ADXL345_ADDRESS, ADXL_REGISTER_PWRCTL, ADXL_PWRCTL_MEASURE, ADXL345_REGISTER_XLSB){
  zeroX = 0;
  zeroY = 0;
  zeroZ = 0;
}

/**
 * Saves new values for "0"
 */
//TODO don't use just one value - take a few so we get a good result
void Accelerometer::zero(){
  zeroX = data[XAXIS];
  zeroY = data[YAXIS];
  zeroZ = data[ZAXIS];
}

/**
 * Standardizes Accelerometer readings by converting to degrees and zeroing the data
 * Overrides IMUSensor::convert()
 */
void Accelerometer::convert(){
  toDegrees();
  data[XAXIS] -= zeroX;
  data[YAXIS] -= zeroY;
  data[ZAXIS] -= zeroZ; 
}

/**
 * Takes raw reading and converts it to degrees
 * Precondition: current values in data[] are not already in degrees
 */
void Accelerometer::toDegrees(){
  float x = data[XAXIS];
  float y = data[YAXIS];
  float z = data[ZAXIS];
  
  //57.29578 is 180 / pi
  float xA = tan( x / sqrt( sq(y)+sq(z) ) )  * 57.296; 
  float yA = atan2( y , sqrt( sq(x)+sq(z) ) )  * 57.296;
  float zA = atan2( sqrt( sq(y)+sq(x) ) , z  )  * 57.296;
  
  data[XAXIS] = xA;
  data[YAXIS] = yA;
  data[ZAXIS] = zA;
}

