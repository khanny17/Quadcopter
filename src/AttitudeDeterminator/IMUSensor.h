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

#define ZERO_SAMPLE_COUNT 10 //number of samples to take when zeroing the sensor

struct PRY
{
    double pitch, roll, yaw;
}

class IMUSensor
{
    public:
        IMUSensor(boost::shared_ptr<IMU> imu, int address, char initRegister, char i2cWriteData, char readRegister);
        PRY getData(); //Puts data for an axis into passed pointer
        void findZero();
    protected:
        boost::shared_ptr<IMU> m_imu; //pointer to an IMU object
        int m_address;
        char m_initRegister, m_i2cWriteData, m_readRegister;
        PRY m_data;
        PRY m_zero;
        void initSensor();
        void readSensor(); //Reads in new values and calls convert
        virtual void zeroData();
        virtual void convert() = 0; //converts raw data to usable units
};

#endif
