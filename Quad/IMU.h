/**
 *  Module for reading info from the sparkfun 9DOF Sensor Stick
 *
 *  Adapted from: http://robotosh.blogspot.com/2012/03/sparkfun-9dof-imu-sensor-stick.html
 */
#ifndef IMU_h
#define IMU_h

#include "Arduino.h"
#include "Wire.h"
#include "Util.h"

#define  ADXL345_ADDRESS (0xA6 >> 1)
//There are 6 data registers, they are sequential starting 
//with the LSB of X.  We'll read all 6 in a burst and won't
//address them individually
#define ADXL345_REGISTER_XLSB (0x32)

//Need to set power control bit to wake up the adxl345
#define ADXL_REGISTER_PWRCTL (0x2D)
#define ADXL_PWRCTL_MEASURE (1 << 3)


#define ITG3200_ADDRESS (0xD0 >> 1)
//request burst of 6 bytes from this address
#define ITG3200_REGISTER_XMSB (0x1D)
#define ITG3200_REGISTER_DLPF_FS (0x16)
#define ITG3200_FULLSCALE (0x03 << 3)
#define ITG3200_42HZ (0x03)


#define HMC5843_ADDRESS (0x3C >> 1)
//First data address of 6 is XMSB.  Also need to set a configuration register for
//continuous measurement
#define HMC5843_REGISTER_XMSB (0x03)
#define HMC5843_REGISTER_MEASMODE (0x02)
#define HMC5843_MEASMODE_CONT (0x00)


class IMU
{
    public:
        IMU();
        void i2c_write(int address, byte reg, byte data);
        void i2c_read(int address, byte reg, int count, byte* data);  
        void init_adxl345();
        void read_adxl345();
        void init_itg3200();
        void read_itg3200();
        void init_hmc5843();
        void read_hmc5843();
        XYZ<int> get_accelerometer_data();
        XYZ<int> get_gyroscope_data();
        XYZ<int> get_magnetometer_data();

    private:
        XYZ<int> accelerometer_data;
        XYZ<int> gyro_data;
        XYZ<int> magnetometer_data;
        void print_data(XYZ<int> data);

};

#endif
