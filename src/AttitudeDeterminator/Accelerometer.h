/**
 * Subclass of IMUSensor that implements the Accelerometer
 */
#ifndef Accelerometer_h
#define Accelerometer_h

#include <math.h>
#include <boost/shared_ptr.hpp>
#include <boost/property_tree/ptree.hpp>
#include "IMUSensor.h"

class Accelerometer: public IMUSensor
{
    public:
        Accelerometer(boost::shared_ptr<IMU> imu,
                      boost::shared_ptr<boost::property_tree::ptree> config);
    private:
        void convert();
};

#endif
