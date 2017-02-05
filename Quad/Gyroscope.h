/**
 * Subclass of IMUSensor that implements the Gyroscope
 */
#ifndef Gyroscope_h
#define Gyroscope_h

#include "IMU.h"

#define GYRO_RAW_SCALING_FACTOR 14.375

class Gyroscope
{
    public:
        Gyroscope(IMU *t_imu);
        void update();
        XYZ<double> getData() const;
      
    private:
        IMU *m_imu;
        XYZ<double> m_data;
        XYZ<double> convert(const XYZ<int>& raw) const;
};

#endif
