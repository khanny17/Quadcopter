#ifndef KalmanFilter_h
#define KalmanFilter_h

#include "Filter.h"

struct State{
  float angle;
  float bias;
};

class KalmanFilter : public Filter
{
  public:
    KalmanFilter(float Q_angle, float Q_bias, float R);
    void init(float initial, float P_00, float P_11);
    float filter(float accReading, float gyroReading);
  private:
    void predictAPrioriEstimate(float gyroReading, float delta_t);
    void predictAPrioriCovariance(float delta_t);
    void calcInnovation(float accReading);
    void calcInnovationCovariance();
    void calcKalmanGain();
    void calcAPosterioriEstimate();
    void calcAPosterioriCovariance();
  
    State aPrioriEstimate;
    State aPosterioriEstimate; //Used as the previousEstimate for next cycle
    float aPrioriCovariance[2][2];
    float aPosterioriCovariance[2][2]; //Used as previousCovariance for next cycle

    State kalmanGain;
    
    float innovation, innovationCovariance;
    float Q_angle, Q_bias, R;
    unsigned long t_prev;
};

#endif
