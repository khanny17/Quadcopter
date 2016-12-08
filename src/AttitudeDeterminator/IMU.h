/**
 *  Module for reading info from the adafruit 9DOF Sensor Stick
 *
 *  Adapted from: http://robotosh.blogspot.com/2012/03/sparkfun-9dof-imu-sensor-stick.html
 */
#ifndef IMU_h
#define IMU_h

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <boost/log/trivial.hpp>

class IMU
{
    public:
        IMU();
        void i2cWrite(int address, char reg, char data);
        void i2cRead(int address, char reg, int count, char *data);
    private:
        int m_fd;
};

#endif
