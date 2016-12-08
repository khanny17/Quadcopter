/**
 * Determines attitude of the quadcopter using sensors and filters
 */
#include "AttitudeDeterminator.h"

using namespace boost;
using namespace boost::property_tree;

/**
 * Instantiates sensors and filter
 */
AttitudeDeterminator::AttitudeDeterminator(shared_ptr<ptree> config){
    m_imu.reset(new IMU);
    m_accelerometer.reset(new Accelerometer(m_imu, config));
    m_gyroscope.reset(new Gyroscope(m_imu, config));

    //pitchFilter = new ComplimentaryFilter(K_GYRO);
    m_pitchFilter.reset(new KalmanFilter(1,1,1));
    m_rollFilter.reset(new ComplimentaryFilter(config->get<double>("Filters.K_GYRO")));
    m_yawFilter.reset(new ComplimentaryFilter(config->get<double>("Filters.K_GYRO")));

    //Start thread
    m_thread.reset(new std::thread(&AttitudeDeterminator::updateAttitudeThread, this));
}

void AttitudeDeterminator::updateAttitudeThread(){
    m_run = true;
    BOOST_LOG_TRIVIAL(info) << "Entering AttitudeDeterminator update thread";

    while(m_run){
        PRY acc = m_accelerometer->getData();
        PRY gyro = m_gyroscope->getData();

        m_attitude.pitch = m_pitchFilter->filter(acc.pitch, gyro.pitch);
        m_attitude.roll = 0; //TODO implement these two
        m_attitude.yaw = 0;
    }

    BOOST_LOG_TRIVIAL(warning) << "Exiting AttitudeDeterminator update thread";
}

PRY AttitudeDeterminator::getAttitude(){
    return m_attitude;
}
