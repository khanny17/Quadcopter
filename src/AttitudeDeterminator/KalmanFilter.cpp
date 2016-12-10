#include "KalmanFilter.h"

using namespace boost;
using namespace boost::posix_time;

KalmanFilter::KalmanFilter(float t_Q_angle, float t_Q_bias, float t_R){
    m_Q_angle = t_Q_angle;
    m_Q_bias = t_Q_bias;
    m_R = t_R;
    curTime.reset();
    prevTime.reset(new ptime(microsec_clock::local_time()));
    //TODO Double check all the init values
    init(0, 0, 0);
    m_kalmanGain.angle = 0;
    m_kalmanGain.bias = 0;
    m_innovation = 0;
    m_innovationCovariance = 0;
}

/**
 * Initializes the Kalman filter with the starting angles and starting errors.
 * P_00 can either be set to a very large number or 0, depending on if you 
 * calibrate the system beforehand or not
 */
void KalmanFilter::init(float initial, float P_00, float P_11){
    m_aPrioriEstimate.angle = 0;
    m_aPrioriEstimate.bias = 0;

    m_aPosterioriEstimate.angle = initial;
    m_aPosterioriEstimate.bias = 0;

    m_aPrioriCovariance[0][0] = 0;
    m_aPrioriCovariance[0][1] = 0;
    m_aPrioriCovariance[1][0] = 0;
    m_aPrioriCovariance[1][1] = 0;

    m_aPosterioriCovariance[0][0] = P_00;
    m_aPosterioriCovariance[0][1] = 0;
    m_aPosterioriCovariance[1][0] = 0;
    m_aPosterioriCovariance[1][1] = P_11;
}

double KalmanFilter::filter(double accReading, double gyroReading){
    curTime.reset(new ptime(microsec_clock::local_time()));

    //Integrate gyro reading:
    time_duration diff = *curTime - *prevTime;
    unsigned long delta_t_ms = diff.total_milliseconds();
    float delta_t = (float)(delta_t_ms)/1000; //convert to seconds (with precision)

    predictAPrioriEstimate(gyroReading, delta_t);
    predictAPrioriCovariance(delta_t);
    calcInnovation(accReading);
    calcInnovationCovariance();
    calcKalmanGain();
    calcAPosterioriEstimate();
    calcAPosterioriCovariance();

    prevTime.swap(curTime);

    return m_aPosterioriEstimate.angle;
}

/**
 * Predict the next orientation based on previous estimate and the gyro values
 */
void KalmanFilter::predictAPrioriEstimate(float gyroReading, float delta_t){
    //Maths have been simplified!
    float angle  = m_aPosterioriEstimate.angle;
    float bias = m_aPosterioriEstimate.bias;
    m_aPrioriEstimate.angle = (angle + delta_t * (gyroReading - bias));

    //Pass on the bias values without changing them
    m_aPrioriEstimate.bias = m_aPosterioriEstimate.bias;
}

/**
 * Predict our error
 */
void KalmanFilter::predictAPrioriCovariance(float delta_t){
    float P_00 = m_aPosterioriCovariance[0][0];
    float P_01 = m_aPosterioriCovariance[0][1];  //TODO make sure these are the correct indices
    float P_10 = m_aPosterioriCovariance[1][0];
    float P_11 = m_aPosterioriCovariance[1][1];

    //Maths have been simplified!
    m_aPrioriCovariance[0][0] = (P_00 + (delta_t * (m_Q_angle - P_10 - P_01 + (delta_t * P_11)) ) );
    m_aPrioriCovariance[0][1] = (P_01 - (delta_t * P_11));
    m_aPrioriCovariance[1][0] = (P_10 - (delta_t * P_11));
    m_aPrioriCovariance[1][1] = (P_11 + (delta_t * m_Q_bias));
}

/**
 * Calculate the innovation vector (transposed)
 */
void KalmanFilter::calcInnovation(float accReading){
    m_innovation = accReading - m_aPrioriEstimate.angle;
}

/**
 * Calculate error of the innovation
 */
void KalmanFilter::calcInnovationCovariance(){
    m_innovationCovariance = m_aPrioriCovariance[0][0] + m_R;
}

/**
 * Calculate the kalman gains used to control input of the innovation to the final estimate
 */
void KalmanFilter::calcKalmanGain(){
    m_kalmanGain.angle = m_aPrioriCovariance[0][0] / m_innovationCovariance;
    m_kalmanGain.bias = m_aPrioriCovariance[1][0] / m_innovationCovariance;
}

/**
 * Calculate our final estimate of the angles and their bias'
 */
void KalmanFilter::calcAPosterioriEstimate(){
    m_aPosterioriEstimate.angle = m_aPrioriEstimate.angle + m_kalmanGain.angle * m_innovation;  //pitch_Estimate + kalman * pitch_Acc

    m_aPosterioriEstimate.bias = m_aPrioriEstimate.bias + m_kalmanGain.bias * m_innovation; //pitch_bias_Estimate + kalman * pitch_Acc
}

void KalmanFilter::calcAPosterioriCovariance(){
    float K_0 = m_kalmanGain.angle;
    float K_1 = m_kalmanGain.bias;
    float P_00 = m_aPrioriCovariance[0][0];
    float P_01 = m_aPrioriCovariance[0][1];
    float P_10 = m_aPrioriCovariance[1][0];
    float P_11 = m_aPrioriCovariance[1][1];

    m_aPosterioriCovariance[0][0] = ( P_00 * (1 - K_0) );
    m_aPosterioriCovariance[0][1] = ( P_01 * (1 - K_0) );
    m_aPosterioriCovariance[1][0] = ( P_10 - P_00 * K_1);
    m_aPosterioriCovariance[1][1] = ( P_11 - P_01 * K_1 );
}
