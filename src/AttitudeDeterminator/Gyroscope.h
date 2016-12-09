/**
 * Subclass of IMUSensor that implements the Gyroscope
 */
#ifndef Gyroscope_h
#define Gyroscope_h

#include <boost/shared_ptr.hpp>
#include <boost/property_tree/ptree.hpp>
#include "IMUSensor.h"

class Gyroscope: public IMUSensor
{
    public:
        Gyroscope(boost::shared_ptr<IMU> imu,
                  boost::shared_ptr<boost::property_tree::ptree> config);
    private:
        void convert();
        void zeroData();
        double GYRO_RAW_SCALING_FACTOR;
};

#endif
