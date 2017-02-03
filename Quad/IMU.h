/**
 *  Module for reading info from the adafruit 9DOF Sensor Stick
 *
 *  Adapted from: http://robotosh.blogspot.com/2012/03/sparkfun-9dof-imu-sensor-stick.html
 */
#ifndef IMU_h
#define IMU_h

#include "Arduino.h"
#include "Wire.h"

class IMU
{
  public:
    IMU();
    void i2cWrite(int address, byte reg, byte data);
    void i2cRead(int address, byte reg, int count, byte* data);
};

#endif
