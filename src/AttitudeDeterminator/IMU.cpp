/** 
 *  Module for reading info from the adafruit 9DOF Sensor Stick
 *
 *  Adapted from: http://robotosh.blogspot.com/2012/03/sparkfun-9dof-imu-sensor-stick.html
 */

#include "IMU.h"

IMU::IMU(){
    //Wire.begin();
    auto filename = "/dev/i2c-1";
    m_fd = open(filename, O_RDWR);
    if(m_fd < 0) {
        auto msg = "Failed to open i2c port";
        BOOST_LOG_TRIVIAL(error) << msg;
        throw msg;
    }
}

void IMU::i2cWrite(int address, char reg, char data) {
    //Wire.beginTransmission(address);
    //Wire.write(reg);
    //Wire.write(data);
    //Wire.endTransmission();

    if(ioctl(m_fd, I2C_SLAVE, address) < 0) {
        auto msg = "Unable to get bus access to talk to slave";
        BOOST_LOG_TRIVIAL(error) << msg;
        throw msg;
    }

    if(write(m_fd, &reg, data) != 1) {
        auto msg = "Error writing to slave";
        BOOST_LOG_TRIVIAL(error) << msg;
        throw msg;
    }
}

void IMU::i2cRead(int address, char reg, int count, char *data) {
    //int i = 0;
    //char c;
    //
    //Wire.beginTransmission(address);
    //Wire.write(reg);
    //Wire.endTransmission();
    //Wire.beginTransmission(address);
    //Wire.requestFrom(address,count);
    //while(Wire.available()){
    //  c = Wire.read();
    //  data[i] = c;
    //  i++;
    //}
    //Wire.endTransmission();

    if(ioctl(m_fd, I2C_SLAVE, address) < 0) {
        auto msg = "Unable to get bus access to talk to slave";
        BOOST_LOG_TRIVIAL(info) << msg;
        throw msg;
    }

    if (read(m_fd, data, count) != count) {
        auto msg = "Unable to read from slave";
        BOOST_LOG_TRIVIAL(info) << msg;
        throw msg;
    }
} 

