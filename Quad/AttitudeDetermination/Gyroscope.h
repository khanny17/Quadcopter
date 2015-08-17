/**
 * Subclass of IMUSensor that implements the Gyroscope
 */
#ifndef Gyroscope_h
#define Gyroscope_h

#include "IMUSensor.h"

#define ITG3200_ADDRESS (0xD0 >> 1)
#define ITG3200_REGISTER_XMSB (0x1D)
#define ITG3200_REGISTER_DLPF_FS (0x16)
#define ITG3200_FULLSCALE (0x03 << 3)
#define ITG3200_42HZ (0x03) //TODO THIS WAS ORIGINALLY (0x03)

#define GYRO_RAW_SCALING_FACTOR 14.375

class Gyroscope: public IMUSensor
{
  public:
    Gyroscope(IMU* imu);
  private:
    void convert();
};

#endif
