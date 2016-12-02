/**
 * Abstract class to define standard methods for each sensor on the IMU board
 * 
 * Originally adapted from: http://robotosh.blogspot.com/2012/03/sparkfun-9dof-imu-sensor-stick.html
 */
#ifndef IMUSensor_h
#define IMUSensor_h

#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>
#include "IMU.h"

#define XAXIS 0
#define YAXIS 1
#define ZAXIS 2

#define ZERO_SAMPLE_COUNT 10 //number of samples to take when zeroing the sensor

class IMUSensor
{
  public:
    explicit IMUSensor(boost::shared_ptr<IMU> imu, int address, char initRegister, char i2cWriteData, char readRegister);
    bool getData(int axis, float* data); //Puts data for an axis into passed pointer
    void findZero();
  protected:
    boost::shared_ptr<IMU> m_imu; //pointer to an IMU object
    int m_address;
    char m_initRegister, m_i2cWriteData, m_readRegister;
    float m_data[3];
    float m_zero[3];
    void initSensor();
    void readSensor(); //Reads in new values and calls convert
    virtual void zeroData();
    virtual void convert() = 0; //converts raw data to usable units
};

#endif
