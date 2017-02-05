#include "Accelerometer.h"

Accelerometer::Accelerometer(IMU *t_imu, double t_smoothingFactor) :
    m_imu(t_imu),
    m_smoothingFactor(t_smoothingFactor) {
    m_imu->init_adxl345();
    m_prev_raw = { 0, 0, 0 };
    m_zero = { 0, 0, 0 };
    m_data = { 0, 0, 0 };
}

void Accelerometer::calc_zero(const int numSamples) {
    XYZ<double> average = { 0, 0, 0 };
    for(int i = 0; i < numSamples; ++i) {
        m_imu->read_adxl345();
        XYZ<int> raw = m_imu->get_accelerometer_data();
        filter(raw);
        Serial.print("Before conversion: ");
        Util::print_xyz(raw);
        XYZ<double> converted = convert(raw);
        Serial.print("After conversion: ");
        Util::print_xyz(converted);
        
        //slower than summing and then dividing, but less chance of overflow when high num samples
        average.x += converted.x / numSamples;  
        delay(50);
    }
    m_zero = average;
    Serial.print("Accelerometer zero: ");
    Util::print_xyz(m_zero);
}

void Accelerometer::update() {
    m_imu->read_adxl345();
    XYZ<int> raw = m_imu->get_accelerometer_data();
    filter(raw);
    XYZ<double> converted = convert(raw);
    zero_data(converted);
    m_data = converted;
}

void Accelerometer::filter(XYZ<int>& raw) {
    static double inverseSmoothingFactor = 1 - m_smoothingFactor; //calculate the inverse just one time
    
    raw.x = (m_smoothingFactor * raw.x) + (inverseSmoothingFactor * m_prev_raw.x);
    raw.y = (m_smoothingFactor * raw.y) + (inverseSmoothingFactor * m_prev_raw.y);
    raw.z = (m_smoothingFactor * raw.z) + (inverseSmoothingFactor * m_prev_raw.z);
    
    m_prev_raw = raw; //Save our new "previous" values for the next time we execute
}

XYZ<double> Accelerometer::convert(const XYZ<int>& raw) const {
    XYZ<double> converted;

    //Serial.println(" ---------- ");
    //double y2 = sq(raw.y);
    //Serial.print("y2: "); Serial.println(y2);
    //double z2 = sq(raw.z);
    //Serial.print("z2: "); Serial.println(z2);
    //double YZ = y2 + z2;
    //Serial.print("YZ: "); Serial.println(YZ);
    //double sqrtYZ = sqrt(YZ);
    //Serial.print("sqrtYZ: "); Serial.println(sqrtYZ);
    //double xOverSqrtYZ = raw.x / sqrtYZ;
    //Serial.print("xOverSqrtYZ: "); Serial.println(xOverSqrtYZ);
    //double final = tan(xOverSqrtYZ);
    //Serial.print("final: "); Serial.println(final);




   
    //57.29578 is 180 / pi
    converted.x = tan( raw.x / sqrt( sq((long)raw.y)+sq((long)raw.z) ) )  * 57.296; 
    converted.y = atan2( raw.y , sqrt( sq((long)raw.x)+sq((long)raw.z) ) )  * 57.296;
    converted.z = atan2( sqrt( sq((long)raw.y)+sq((long)raw.x) ) , raw.z  )  * 57.296;
  
    return converted;
}

void Accelerometer::zero_data(XYZ<double>& original) const {
    original.x -= m_zero.x;
    original.y -= m_zero.y;
    original.z -= m_zero.z;
}


XYZ<double> Accelerometer::getData() {
    return m_data;
}
