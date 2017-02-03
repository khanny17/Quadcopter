/**
 * Subclass of IMUSensor that implements the Accelerometer
 */
#include "Accelerometer.h"

/**
 * Call super constructor with our constant values and zero sensor
 */
Accelerometer::Accelerometer(IMU* imu, double smoothingFactor) : 
IMUSensor(imu, ADXL345_ADDRESS, ADXL_REGISTER_PWRCTL, ADXL_PWRCTL_MEASURE, ADXL345_REGISTER_XLSB){
  m_smoothingFactor = smoothingFactor;
  if(m_smoothingFactor > 1 || m_smoothingFactor < 0) {
      Serial.println("WARNING: Accelerometer:: Invalid Smoothing Factor");
  }
  initSensor();
  findZero();
}

/**
 * Takes raw reading and converts it to degrees
 * Precondition: current values in data[] are not already in degrees
 */
XYZ<double> Accelerometer::convert(const XYZ<int>& readings){
  double x = readings.x;
  double y = readings.y;
  double z = readings.z;

  //Low pass filter
  
  
  //57.29578 is 180 / pi
  double xA = tan( x / sqrt( sq(y)+sq(z) ) )  * 57.296; 
  double yA = atan2( y , sqrt( sq(x)+sq(z) ) )  * 57.296;
  double zA = atan2( sqrt( sq(y)+sq(x) ) , z  )  * 57.296;

  return {
      zA,
      yA,
      zA
  };
}

