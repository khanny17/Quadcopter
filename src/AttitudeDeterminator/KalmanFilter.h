#ifndef KalmanFilter_h
#define KalmanFilter_h

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/scoped_ptr.hpp>

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

        State m_aPrioriEstimate;
        State m_aPosterioriEstimate; //Used as the previousEstimate for next cycle
        float m_aPrioriCovariance[2][2];
        float m_aPosterioriCovariance[2][2]; //Used as previousCovariance for next cycle

        State m_kalmanGain;

        float m_innovation, m_innovationCovariance;
        float m_Q_angle, m_Q_bias, m_R;
        boost::scoped_ptr<boost::posix_time::ptime> curTime, prevTime;
};

#endif
