/**
 * Determines attitude of the quadcopter using sensors and filters
 */
#include "AttitudeDeterminator.h"

/**
 * Instantiates sensors and filter
 */
AttitudeDeterminator::AttitudeDeterminator(float K_GYRO){
    m_imu.reset(new IMU);
    m_accelerometer.reset(new Accelerometer(m_imu));
    m_gyroscope.reset(new Gyroscope(m_imu));

    //pitchFilter = new ComplimentaryFilter(K_GYRO);
    m_pitchFilter.reset(new KalmanFilter(1,1,1));
    m_rollFilter.reset(new ComplimentaryFilter(K_GYRO));
    m_yawFilter.reset(new ComplimentaryFilter(K_GYRO));
}

/**
 *  Fills passed pointers with their respective angle readings
 */
void AttitudeDeterminator::getAttitude(float* pitch, float* roll, float* yaw){
    float accPitchReading, gyroPitchReading;
    m_accelerometer->getData(YAXIS, &accPitchReading);
    m_gyroscope->getData(YAXIS, &gyroPitchReading);

    *pitch = m_pitchFilter->filter(accPitchReading, gyroPitchReading);
    *roll = 0;
    *yaw = 0;
}


