#include "Gyroscope.h"

/**
 * Call super constructor with our constant values,
 */
Gyroscope::Gyroscope(IMU *t_imu) : m_imu(t_imu) {
    m_imu->init_itg3200();
}

void Gyroscope::update() {
    m_imu->read_itg3200();
    XYZ<int> raw = m_imu->get_gyroscope_data();
    m_data = convert(raw);
}

XYZ<double> Gyroscope::getData() const {
    return m_data;
}

/**
 * Converts Gyroscope to degrees per second by dividing by a scaling factor
 */
XYZ<double> Gyroscope::convert(const XYZ<int>& raw) const {
    return {
        ((double)raw.x) / GYRO_RAW_SCALING_FACTOR,
        ((double)raw.y) / GYRO_RAW_SCALING_FACTOR,
        ((double)raw.z) / GYRO_RAW_SCALING_FACTOR
    };
}

