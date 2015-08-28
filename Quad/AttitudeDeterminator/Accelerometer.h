/**
 * Subclass of IMUSensor that implements the Accelerometer
 */
#ifndef Accelerometer_h
#define Accelerometer_h

#include "IMUSensor.h"

#define ADXL345_ADDRESS (0xA6 >> 1)
#define ADXL345_REGISTER_XLSB (0x32)
#define ADXL_REGISTER_PWRCTL (0x2D)
#define ADXL_PWRCTL_MEASURE (1 << 3)

#define ZERO_SAMPLE_COUNT 10 //number of samples to take when zeroing the accelerometer

class Accelerometer: public IMUSensor
{
  public:
    Accelerometer(IMU* imu);
    void zero();
  private:
    void convert();
    void toDegrees();
    float zeroX, zeroY, zeroZ;
};

#endif
