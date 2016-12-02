/**
 * Abstract class to define standard methods for each sensor on the IMU board
 * 
 * Originally adapted from: http://robotosh.blogspot.com/2012/03/sparkfun-9dof-imu-sensor-stick.html
 */
#include "IMUSensor.h"

using namespace boost;

/**
 * Constructs a new IMUSensor object, saving the passed values and initializing other member variables
 */
IMUSensor::IMUSensor(IMU* t_imu, int t_address, char t_initRegister, char t_i2cWriteData, char t_readRegister){
    m_imu = t_imu;
    m_address = t_address;
    m_initRegister = t_initRegister;
    m_i2cWriteData = t_i2cWriteData;
    m_readRegister = t_readRegister;
    //Set data and zero values to 0
    for(int i = 0; i < 3; ++i){
        m_data[i] = 0;
        m_zero[i] = 0;
    }
}

/**
 * Puts sensor reading for a given axis into the passed "data" pointer.
 * Returns: true if successfully executed
 *          false if invalid axis given
 */
bool IMUSensor::getData(int axis, float* t_data){
    readSensor();
    if(axis == XAXIS || axis == YAXIS || axis == ZAXIS){
        *t_data = m_data[axis];
        return true;
    } else {
        return false;
    }
}

/**
 * Talks to IMU and initializes sensor
 */
void IMUSensor::initSensor(){
    char data = 0;
    m_imu->i2cWrite(m_address, m_initRegister, m_i2cWriteData);
    //Use to check what we just wrote: imu->i2cRead(address, initRegister, 1, &data);
    findZero();
}

/**
 * Reads new data from the IMU
 */
void IMUSensor::readSensor(){
    char chars[6] = {};

    m_imu->i2cRead(m_address, m_readRegister, 6, chars);

    for (int i = 0; i < 3; ++i) {
        m_data[i] = (int)chars[2*i] + (((int)chars[2*i + 1]) << 8);
    }
    convert();
    zeroData();
}

/**
 * Zero the data based on our previous values for zero
 */
void IMUSensor::zeroData(){
    m_data[XAXIS] -= m_zero[XAXIS];
    m_data[YAXIS] -= m_zero[YAXIS];
    m_data[ZAXIS] -= m_zero[ZAXIS];
}

/**
 * Get sensor reading when quadcopter is perfectly flat and not moving and save as 0 value
 */
void IMUSensor::findZero(){
    float x = 0, y = 0, z = 0;
    for(int i = 0; i < ZERO_SAMPLE_COUNT; ++i){
        readSensor();
        x += m_data[XAXIS];
        y += m_data[YAXIS];
        z += m_data[ZAXIS];
        this_thread::sleep_for(chrono::milliseconds(10));
    }

    m_zero[XAXIS] = x/ZERO_SAMPLE_COUNT;
    m_zero[YAXIS] = y/ZERO_SAMPLE_COUNT;
    m_zero[ZAXIS] = z/ZERO_SAMPLE_COUNT;
}
