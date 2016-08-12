/**
 *  Module for reading info from the adafruit 9DOF Sensor Stick
 *
 *  Adapted from: http://robotosh.blogspot.com/2012/03/sparkfun-9dof-imu-sensor-stick.html
 */
#ifndef IMU_h
#define IMU_h

//#include "Wire.h"

class IMU
{
  public:
    IMU();
    void i2cWrite(int address, char reg, char data);
    void i2cRead(int address, char reg, int count, char *data);
};

#endif
