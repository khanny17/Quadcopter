#include "Kalman.h"
#include "Arduino.h"

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
void KalmanFilter::init(float pitch, float roll, float yaw, float P_00, float P_11){
  aPrioriEstimate.clear();
  
  aPosterioriEstimate.clear(); //set all values to 0
  aPosterioriEstimate.set(0,0,pitch);
  aPosterioriEstimate.set(0,1,roll);
  aPosterioriEstimate.set(0,2,yaw);

  aPrioriCovariance.clear();

  aPosterioriCovariance.clear();
  aPosterioriCovariance.set(0,0, P_00);
  aPosterioriCovariance.set(1,1, P_11);
}

PRY KalmanFilter::getOrientation(PRY acc_angles, PRY gyro_rates){
  float delta_t = (float)(millis() - t_prev)/1000;
  
  predictAPrioriEstimate(gyro_rates, delta_t);
  predictAPrioriCovariance(delta_t);
  calcInnovation(acc_angles);
  calcInnovationCovariance();
  calcKalmanGain();
  calcAPosterioriEstimate();
  calcAPosterioriCovariance();
  
  t_prev = millis();
  
  return (PRY){ 
    aPosterioriEstimate.get(0,0),
    aPosterioriEstimate.get(0,1),
    aPosterioriEstimate.get(0,2)
  };
}

/**
 * Predict the next orientation based on previous estimate and the gyro values
 */
void KalmanFilter::predictAPrioriEstimate(PRY gyro_rates, float delta_t){
  //Maths have been simplified!
  float theta_p  = aPosterioriEstimate.get(0,0);
  float omega_pb = aPosterioriEstimate.get(1,0);
  float omega_p_gyro = gyro_rates.pitch;
  aPrioriEstimate.set(0,0, theta_p + delta_t * (omega_p_gyro - omega_pb));

  float theta_r  = aPosterioriEstimate.get(0,1);
  float omega_rb = aPosterioriEstimate.get(1,1);
  float omega_r_gyro = gyro_rates.roll;
  aPrioriEstimate.set(0,1, theta_r + delta_t * (omega_r_gyro - omega_rb));

  float theta_y  = aPosterioriEstimate.get(0,2);
  float omega_yb = aPosterioriEstimate.get(1,2);
  float omega_y_gyro = gyro_rates.yaw;
  aPrioriEstimate.set(0,2, theta_y + delta_t * (omega_y_gyro - omega_yb));

  //Pass on the bias values without changing them
  aPrioriEstimate.set(1,0, aPosterioriEstimate.get(1,0));
  aPrioriEstimate.set(1,1, aPosterioriEstimate.get(1,1));
  aPrioriEstimate.set(1,2, aPosterioriEstimate.get(1,2));
}

/**
 * Predict our error
 */
void KalmanFilter::predictAPrioriCovariance(float delta_t){
  float P_00 = aPosterioriCovariance.get(0,0);
  float P_01 = aPosterioriCovariance.get(0,1);
  float P_10 = aPosterioriCovariance.get(1,0);
  float P_11 = aPosterioriCovariance.get(1,1);

  //Maths have been simplified!
  aPrioriCovariance.set(0,0, P_00 + (delta_t * (Q_angle - P_10 - P_01 + (delta_t * P_11)) ) );
  aPrioriCovariance.set(0,1, P_01 - (delta_t * P_11));
  aPrioriCovariance.set(1,0, P_10 - (delta_t * P_11));
  aPrioriCovariance.set(1,1, P_11 + (delta_t * Q_bias));
}

/**
 * Calculate the innovation vector (transposed)
 */
void KalmanFilter::calcInnovation(PRY acc_angles){
  innovation.set(0,0, acc_angles.pitch - aPrioriEstimate.get(0,0)); // accelerometer reading - estimate
  innovation.set(0,1, acc_angles.roll - aPrioriEstimate.get(0,1));
  innovation.set(0,2, acc_angles.yaw - aPrioriEstimate.get(0,2));
}

/**
 * Calculate error of the innovation
 */
void KalmanFilter::calcInnovationCovariance(){
  innovationCovariance = aPrioriCovariance.get(0,0) + R;
}

/**
 * Calculate the kalman gains used to control input of the innovation to the final estimate
 */
void KalmanFilter::calcKalmanGain(){
  kalmanGain.set(0,0, aPrioriCovariance.get(0,0) / innovationCovariance);
  kalmanGain.set(1,0, aPrioriCovariance.get(1,0) / innovationCovariance);
}

/**
 * Calculate our final estimate of the angles and their bias'
 */
void KalmanFilter::calcAPosterioriEstimate(){
  float theta_p = aPrioriEstimate.get(0,0);
  aPosterioriEstimate.set(0,0, theta_p + kalmanGain.get(0,0) * innovation.get(0,0) );  //pitch_Estimate + kalman * pitch_Acc
  
  float theta_r = aPrioriEstimate.get(0,1);
  aPosterioriEstimate.set(0,1, theta_r + kalmanGain.get(0,0) * innovation.get(0,1) );  //roll_Estimate + kalman * roll_Acc
  
  float theta_y = aPrioriEstimate.get(0,2);
  aPosterioriEstimate.set(0,2, theta_y + kalmanGain.get(0,0) * innovation.get(0,2) );  //yaw_Estimate + kalman * yaw_Acc

  float theta_pb = aPrioriEstimate.get(1,0);
  aPosterioriEstimate.set(1,0, theta_pb + kalmanGain.get(1,0) * innovation.get(0,0) ); //pitch_bias_Estimate + kalman * pitch_Acc
  
  float theta_rb = aPrioriEstimate.get(1,1);
  aPosterioriEstimate.set(1,1, theta_rb + kalmanGain.get(1,0) * innovation.get(0,1) ); //roll_bias_Estimate + kalman * roll_Acc
  
  float theta_yb = aPrioriEstimate.get(1,2);
  aPosterioriEstimate.set(1,2, theta_yb + kalmanGain.get(1,0) * innovation.get(0,2) ); //yaw_bias_Estimate + kalman * yaw_Acc
}

void KalmanFilter::calcAPosterioriCovariance(){
  float K_0 = kalmanGain.get(0,0);
  float K_1 = kalmanGain.get(1,0);
  float P_00 = aPrioriCovariance.get(0,0);
  float P_01 = aPrioriCovariance.get(0,1);
  float P_10 = aPrioriCovariance.get(1,0);
  float P_11 = aPrioriCovariance.get(1,1);

  aPosterioriCovariance.set(0,0, P_00 * (1 - K_0) );
  aPosterioriCovariance.set(0,1, P_01 * (1 - K_0) );
  aPosterioriCovariance.set(1,0, P_10 - P_00 * K_1);
  aPosterioriCovariance.set(1,1, P_11 - P_01 * K_1 );
}

