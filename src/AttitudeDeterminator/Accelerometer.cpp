/**
 * Subclass of IMUSensor that implements the Accelerometer
 */
#include "Accelerometer.h"

using namespace boost;

/**
 * Call super constructor with our constant values and zero sensor
 */
Accelerometer::Accelerometer(shared_ptr<IMU> imu) : 
    IMUSensor(imu, ADXL345_ADDRESS, ADXL_REGISTER_PWRCTL, ADXL_PWRCTL_MEASURE, ADXL345_REGISTER_XLSB){
        initSensor();
    }

/**
 * Takes raw reading and converts it to degrees
 * Precondition: current values in data[] are not already in degrees
 */
void Accelerometer::convert(){
    auto x = m_data[XAXIS];
    auto y = m_data[YAXIS];
    auto z = m_data[ZAXIS];

    //57.29578 is 180 / pi
    auto xA = tan( x / sqrt( pow(y,2)+pow(z,2) ) )  * 57.296; 
    auto yA = atan2( y , sqrt( pow(x,2)+pow(z,2) ) )  * 57.296;
    auto zA = atan2( sqrt( pow(y,2)+pow(x,2) ) , z  )  * 57.296;

    m_data[XAXIS] = xA;
    m_data[YAXIS] = yA;
    m_data[ZAXIS] = zA;
}

