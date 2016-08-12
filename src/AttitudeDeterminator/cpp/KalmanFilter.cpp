#include "KalmanFilter.h"

KalmanFilter::KalmanFilter(float Q_angle, float Q_bias, float R){
  this->Q_angle = Q_angle;
  this->Q_bias = Q_bias;
  this->R = R;
}

/**
 * Initializes the Kalman filter with the starting angles and starting errors.
 * P_00 can either be set to a very large number or 0, depending on if you 
 * calibrate the system beforehand or not
 */
void KalmanFilter::init(float initial, float P_00, float P_11){
  aPrioriEstimate.angle = 0;
  aPrioriEstimate.bias = 0;
  
  aPosterioriEstimate.angle = initial;
  aPosterioriEstimate.bias = 0;

  aPrioriCovariance[0][0] = 0;
  aPrioriCovariance[0][1] = 0;
  aPrioriCovariance[1][0] = 0;
  aPrioriCovariance[1][1] = 0;

  aPosterioriCovariance[0][0] = P_00;
  aPosterioriCovariance[0][1] = 0;
  aPosterioriCovariance[1][0] = 0;
  aPosterioriCovariance[1][1] = P_11;
}

float KalmanFilter::filter(float accReading, float gyroReading){
  float delta_t = (float)(millis() - t_prev)/1000;
  
  predictAPrioriEstimate(gyroReading, delta_t);
  predictAPrioriCovariance(delta_t);
  calcInnovation(accReading);
  calcInnovationCovariance();
  calcKalmanGain();
  calcAPosterioriEstimate();
  calcAPosterioriCovariance();
  
  t_prev = millis();
  
  return aPosterioriEstimate.angle;
}

/**
 * Predict the next orientation based on previous estimate and the gyro values
 */
void KalmanFilter::predictAPrioriEstimate(float gyroReading, float delta_t){
  //Maths have been simplified!
  float angle  = aPosterioriEstimate.angle;
  float bias = aPosterioriEstimate.bias;
  aPrioriEstimate.angle = (angle + delta_t * (gyroReading - bias));

  //Pass on the bias values without changing them
  aPrioriEstimate.bias = aPosterioriEstimate.bias;
}

/**
 * Predict our error
 */
void KalmanFilter::predictAPrioriCovariance(float delta_t){
  float P_00 = aPosterioriCovariance[0][0];
  float P_01 = aPosterioriCovariance[0][1];  //TODO make sure these are the correct indices
  float P_10 = aPosterioriCovariance[1][0];
  float P_11 = aPosterioriCovariance[1][1];

  //Maths have been simplified!
  aPrioriCovariance[0][0] = (P_00 + (delta_t * (Q_angle - P_10 - P_01 + (delta_t * P_11)) ) );
  aPrioriCovariance[0][1] = (P_01 - (delta_t * P_11));
  aPrioriCovariance[1][0] = (P_10 - (delta_t * P_11));
  aPrioriCovariance[1][1] = (P_11 + (delta_t * Q_bias));
}

/**
 * Calculate the innovation vector (transposed)
 */
void KalmanFilter::calcInnovation(float accReading){
  innovation = accReading - aPrioriEstimate.angle;
}

/**
 * Calculate error of the innovation
 */
void KalmanFilter::calcInnovationCovariance(){
  innovationCovariance = aPrioriCovariance[0][0] + R;
}

/**
 * Calculate the kalman gains used to control input of the innovation to the final estimate
 */
void KalmanFilter::calcKalmanGain(){
  kalmanGain.angle = aPrioriCovariance[0][0] / innovationCovariance;
  kalmanGain.bias = aPrioriCovariance[1][0] / innovationCovariance;
}

/**
 * Calculate our final estimate of the angles and their bias'
 */
void KalmanFilter::calcAPosterioriEstimate(){
  aPosterioriEstimate.angle = aPrioriEstimate.angle + kalmanGain.angle * innovation;  //pitch_Estimate + kalman * pitch_Acc

  aPosterioriEstimate.bias = aPrioriEstimate.bias + kalmanGain.bias * innovation; //pitch_bias_Estimate + kalman * pitch_Acc
}

void KalmanFilter::calcAPosterioriCovariance(){
  float K_0 = kalmanGain.angle;
  float K_1 = kalmanGain.bias;
  float P_00 = aPrioriCovariance[0][0];
  float P_01 = aPrioriCovariance[0][1];
  float P_10 = aPrioriCovariance[1][0];
  float P_11 = aPrioriCovariance[1][1];

  aPosterioriCovariance[0][0] = ( P_00 * (1 - K_0) );
  aPosterioriCovariance[0][1] = ( P_01 * (1 - K_0) );
  aPosterioriCovariance[1][0] = ( P_10 - P_00 * K_1);
  aPosterioriCovariance[1][1] = ( P_11 - P_01 * K_1 );
}
