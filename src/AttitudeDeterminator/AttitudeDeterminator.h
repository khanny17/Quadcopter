/**
 * Determines attitude of the quadcopter using sensors and filters
 */
#ifndef AttitudeDeterminator_h
#define AttitudeDeterminator_h

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/property_tree/ptree.hpp>
#include "Accelerometer.h"
#include "Gyroscope.h"
#include "Filter.h"
#include "KalmanFilter.h"
#include "ComplimentaryFilter.h"


class AttitudeDeterminator
{
    public:
        explicit AttitudeDeterminator(boost::shared_ptr<boost::property_tree::ptree> config);
        void getAttitude(float* pitch, float* roll, float* yaw); //fills passed pointers with angle values
    private:
        boost::shared_ptr<IMU> m_imu;
        boost::scoped_ptr<IMUSensor> m_accelerometer;
        boost::scoped_ptr<IMUSensor> m_gyroscope;
        boost::scoped_ptr<Filter> m_pitchFilter;
        boost::scoped_ptr<Filter> m_rollFilter;
        boost::scoped_ptr<Filter> m_yawFilter;
};


#endif
