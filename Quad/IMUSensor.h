/**
 * Abstract class to define standard methods for each sensor on the IMU board
 * 
 * Originally adapted from: http://robotosh.blogspot.com/2012/03/sparkfun-9dof-imu-sensor-stick.html
 */
#ifndef IMUSensor_h
#define IMUSensor_h

#include "Arduino.h"
#include "IMU.h"

#define XAXIS 0
#define YAXIS 1
#define ZAXIS 2


class IMUSensor
{
  public:
    IMUSensor(IMU* imu, int address, byte initRegister, byte i2cWriteData, byte readRegister);
    bool getData(int axis, float* data); //Puts data for an axis into passed pointer
  protected:
    IMU *imu; //pointer to an IMU object
    int address;
    byte initRegister, i2cWriteData, readRegister;
    float data[3];
    void initSensor();
    void readSensor();
    virtual void convert() = 0; //converts raw data to usable units
};

#endif
