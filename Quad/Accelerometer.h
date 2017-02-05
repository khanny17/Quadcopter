#ifndef Accelerometer_h
#define Accelerometer_h

#include "IMU.h"

class Accelerometer
{
    public:
        Accelerometer(IMU *t_imu, double t_smoothingFactor);
        void update();
        XYZ<double> getData();
        
        void calc_zero(const int numSamples);
      
    private:
        IMU *m_imu;
        double m_smoothingFactor;
        XYZ<int> m_prev_raw;
        XYZ<double> m_data, m_zero;
    
        /**
         *  Given raw unfiltered values, filter them in place
         *  (Modifies passed struct)
         *  Uses Low passed filter with following equation:
         *  x = a * x + (1-a) * x_prev
         *  where a is the smoothingFactor in the range [0,1]
         */
        void filter(XYZ<int>& raw);
    
        /**
         * Takes raw, filtered values and converts it to degrees
         */
        XYZ<double> convert(const XYZ<int>& raw) const;
    
        /**
         * Modifies the passed in struct by zeroing the values
         */
        void zero_data(XYZ<double>& original) const;
};

#endif
