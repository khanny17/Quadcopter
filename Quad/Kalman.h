#ifndef kalman_h
#define kalman_h

#include "Matrix.h"
#include "pry.h" //TODO probably remove the pry struct?

class KalmanFilter
{
  public:
    KalmanFilter(float Q_angle, float Q_bias, float R);
    void init(float pitch, float roll, float yaw,
              float P_00, float P_11);
    PRY getOrientation(PRY acc_angles, PRY gyro_rates);
  private:
    //helper methods
    void predictAPrioriEstimate(PRY gyro_rates, float delta_t);
    void predictAPrioriCovariance(float delta_t);
    void calcInnovation(PRY acc_angles);
    void calcInnovationCovariance();
    void calcKalmanGain();
    void calcAPosterioriEstimate();
    void calcAPosterioriCovariance();

    Matrix aPrioriEstimate{2,3};
    Matrix aPosterioriEstimate{2,3}; //Used as the previousEstimate for next cycle
    Matrix aPrioriCovariance{2,2};
    Matrix aPosterioriCovariance{2,2}; //Used as previousCovariance for next cycle

    Matrix kalmanGain{2,1};
    
    Matrix innovation{1,3};
    float innovationCovariance;
    int Q_angle, Q_bias, R, t_prev;
    
};

#endif
