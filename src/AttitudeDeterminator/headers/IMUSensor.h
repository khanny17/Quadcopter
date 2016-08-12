/**
 * Abstract class to define standard methods for each sensor on the IMU board
 * 
 * Originally adapted from: http://robotosh.blogspot.com/2012/03/sparkfun-9dof-imu-sensor-stick.html
 */
#ifndef IMUSensor_h
#define IMUSensor_h

#include "IMU.h"

#define XAXIS 0
#define YAXIS 1
#define ZAXIS 2

#define ZERO_SAMPLE_COUNT 10 //number of samples to take when zeroing the sensor

class IMUSensor
{
  public:
    IMUSensor(IMU* imu, int address, char initRegister, char i2cWriteData, char readRegister);
    bool getData(int axis, float* data); //Puts data for an axis into passed pointer
    void findZero();
  protected:
    IMU *imu; //pointer to an IMU object
    int address;
    char initRegister, i2cWriteData, readRegister;
    float data[3];
    float zero[3];
    void initSensor();
    void readSensor(); //Reads in new values and calls convert
    virtual void zeroData();
    virtual void convert() = 0; //converts raw data to usable units
};

#endif
