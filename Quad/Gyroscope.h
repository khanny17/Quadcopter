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
#define ITG3200_42HZ (0x03) //The original Low Pass Filter value
#define ITG3200_10HZ (0x05) //Something I am trying now
#define ITG3200_256HZ (0x00) //Something I am trying now


#define GYRO_RAW_SCALING_FACTOR 14.375

class Gyroscope: public IMUSensor
{
  public:
    Gyroscope(IMU* imu);
    void findZero();
  private:
    XYZ<double> convert(const XYZ<int>& readings);
    void zeroData(XYZ<double>& readings);
};

#endif
