/**
 *  Module for reading info from the adafruit 9DOF Sensor Stick
 *
 *  Adapted from: http://robotosh.blogspot.com/2012/03/sparkfun-9dof-imu-sensor-stick.html
 */

#ifndef imu_h
#define imu_h

#include "Arduino.h"
#include "buffer.h"

#define ADXL345_ADDRESS (0xA6 >> 1)
#define ADXL345_REGISTER_XLSB (0x32)
#define ADXL_REGISTER_PWRCTL (0x2D)
#define ADXL_PWRCTL_MEASURE (1 << 3)

#define ITG3200_ADDRESS (0xD0 >> 1)
#define ITG3200_REGISTER_XMSB (0x1D)
#define ITG3200_REGISTER_DLPF_FS (0x16)
#define ITG3200_FULLSCALE (0x03 << 3)
#define ITG3200_42HZ (0x03)

#define HMC5843_ADDRESS (0x3C >> 1)
#define HMC5843_REGISTER_XMSB (0x03)
#define HMC5843_REGISTER_MEASMODE (0x02)
#define HMC5843_MEASMODE_CONT (0x00)

#define X 0
#define Y 1
#define Z 2

#define GYRO_BUFFER_SIZE 20
#define ACC_BUFFER_SIZE 20
#define MAG_BUFFER_SIZE 20

class imu
{
  public:
    imu();
    void prettyPrint();
    void init();
    void update();
    float getAccData(int axis);
    float getGyroData(int axis);
  private:
    int c;
    //Arrays to hold raw values from the sensors
    float accelerometer_data[3];
    float gyro_data[3];
    float magnetometer_data[3];
    //Arrays of buffers to smooth out the readings
    Buffer<float> acc_buffers[3] = {ACC_BUFFER_SIZE, ACC_BUFFER_SIZE, ACC_BUFFER_SIZE};
    Buffer<float> gyro_buffers[3] = {GYRO_BUFFER_SIZE, GYRO_BUFFER_SIZE, GYRO_BUFFER_SIZE};
    Buffer<float> mag_buffers[3] = {MAG_BUFFER_SIZE, MAG_BUFFER_SIZE, MAG_BUFFER_SIZE};
    //Methods for talking to the IMU
    void i2c_write(int address, byte reg, byte data);
    void i2c_read(int address, byte reg, int count, byte* data);
    void init_adxl345();
    void read_adxl345();
    void init_itg3200();
    void read_itg3200();
    void init_hmc5843();
    void read_hmc5843();
    //Helper Methods
    void acc_to_degrees();
    void gyro_to_degrees_per_sec();
    void buffer();
};

#endif
