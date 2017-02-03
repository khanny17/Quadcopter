#include "Gyroscope.h"

/**
 * Call super constructor with our constant values,
 */
Gyroscope::Gyroscope(IMU* imu) : 
IMUSensor(imu, ITG3200_ADDRESS, ITG3200_REGISTER_DLPF_FS, ITG3200_FULLSCALE | ITG3200_42HZ, ITG3200_REGISTER_XMSB){
  initSensor();
  findZero();
}

/**
 * Converts Gyroscope to degrees per second by dividing by a scaling factor
 */
XYZ<double> Gyroscope::convert(const XYZ<int>& readings){
    return {
        ((double)readings.x) / GYRO_RAW_SCALING_FACTOR,
        ((double)readings.y) / GYRO_RAW_SCALING_FACTOR,
        ((double)readings.z) / GYRO_RAW_SCALING_FACTOR
    };
}

/**
 * Override zero functionality to do nothing
 */
void Gyroscope::zeroData(XYZ<double>& readings){
    if(readings.x < zero.x) {
        readings.x = 0;
    }
    
    if(readings.y < zero.y) {
        readings.y = 0;
    }
    
    if(readings.z < zero.z) {
        readings.z = 0;
    }
};

void Gyroscope::findZero(){
    IMUSensor::findZero();

    zero.x *= 2;
    zero.y *= 2;
    zero.z *= 2;

    Serial.println("did it");
    Serial.println(zero.x);
}

