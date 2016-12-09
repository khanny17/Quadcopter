#include "Gyroscope.h"

using namespace boost;
using namespace boost::property_tree;

/**
 * Call super constructor with our constant values,
 */
Gyroscope::Gyroscope(shared_ptr<IMU> imu, shared_ptr<ptree> config) : 
    IMUSensor(imu, 
        config->get<int>("Gyroscope.ITG3200_ADDRESS"), 
        config->get<int>("Gyroscope.ITG3200_REGISTER_DLPF_FS"), 
        config->get<int>("Gyroscope.ITG3200_FULLSCALE") | 
        config->get<int>("Gyroscope.ITG3200_42HZ"), 
        config->get<int>("Gyroscope.ITG3200_REGISTER_XMSB"))
    {
        GYRO_RAW_SCALING_FACTOR = config->get<double>("Gyroscope.GYRO_RAW_SCALING_FACTOR");
        initSensor();
    }

/**
 * Converts Gyroscope to degrees per second by dividing by a scaling factor
 */
void Gyroscope::convert(){
    m_data.roll /= GYRO_RAW_SCALING_FACTOR;
    m_data.pitch /= GYRO_RAW_SCALING_FACTOR;
    m_data.yaw /= GYRO_RAW_SCALING_FACTOR;
}

/**
 * Override zero functionality to do nothing
 */
void Gyroscope::zeroData(){};

