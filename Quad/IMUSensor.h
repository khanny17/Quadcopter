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

#define ZERO_SAMPLE_COUNT 10 //number of samples to take when zeroing the sensor

template <typename T>
struct XYZ {
    T x;
    T y;
    T z;
};

class IMUSensor
{
  public:
    IMUSensor(IMU* imu, int address, byte initRegister, byte i2cWriteData, byte readRegister);
    XYZ<double> updateAndGetData(); //Puts data for an axis into passed pointer'
    virtual void findZero();
  protected:
    IMU *imu; //pointer to an IMU object
    int address;
    byte initRegister, i2cWriteData, readRegister;
    XYZ<double> data;
    XYZ<double> zero;
    void initSensor();
    void update(); //Reads in new values and calls convert
    XYZ<int>& read();
    virtual void zeroData(XYZ<double>& readings);
    virtual XYZ<double> convert(const XYZ<int>& readings) = 0; //converts raw data (stored in longs) to usable units (stored in doubles)
};

#endif
