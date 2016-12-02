#include "Gyroscope.h"

/**
 * Call super constructor with our constant values,
 */
Gyroscope::Gyroscope(IMU* imu) : 
    IMUSensor(imu, ITG3200_ADDRESS, ITG3200_REGISTER_DLPF_FS, ITG3200_FULLSCALE | ITG3200_42HZ, ITG3200_REGISTER_XMSB){
        initSensor();
    }

/**
 * Converts Gyroscope to degrees per second by dividing by a scaling factor
 */
void Gyroscope::convert(){
    m_data[XAXIS] /= GYRO_RAW_SCALING_FACTOR;
    m_data[YAXIS] /= GYRO_RAW_SCALING_FACTOR;
    m_data[ZAXIS] /= GYRO_RAW_SCALING_FACTOR;
}

/**
 * Override zero functionality to do nothing
 */
void Gyroscope::zeroData(){};
