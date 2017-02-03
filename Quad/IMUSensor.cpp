/**
 * Abstract class to define standard methods for each sensor on the IMU board
 * 
 * Originally adapted from: http://robotosh.blogspot.com/2012/03/sparkfun-9dof-imu-sensor-stick.html
 */
#include "IMUSensor.h"

/**
 * Constructs a new IMUSensor object, saving the passed values and initializing other member variables
 */
IMUSensor::IMUSensor(IMU* imu, int address, byte initRegister, byte i2cWriteData, byte readRegister){
    this->imu = imu;
    this->address = address;
    this->initRegister = initRegister;
    this->i2cWriteData = i2cWriteData;
    this->readRegister = readRegister;
    //Set data and zero values to 0
    data.x = 0; data.y = 0; data.z = 0;
    zero.x = 0; zero.y = 0; zero.z = 0;
}

/**
 * Puts sensor reading for a given axis into the passed "data" pointer.
 * Returns: true if successfully executed
 *          false if invalid axis given
 */
XYZ<double> IMUSensor::updateAndGetData(){
    update();
    return data;
}

/**
 * Talks to IMU and initializes sensor
 */
void IMUSensor::initSensor(){
  byte data = 0;
  imu->i2cWrite(address, initRegister, i2cWriteData);
  //Use to check what we just wrote: imu->i2cRead(address, initRegister, 1, &data);
}

/**
 * Reads new data from the IMU
 */
void IMUSensor::update(){
    XYZ<int>& raw = read();  
    XYZ<double> converted = convert(raw);
    zeroData(converted);
    
    data.x = converted.x;
    data.y = converted.y;
    data.z = converted.z;
}

XYZ<int>& IMUSensor::read(){
    byte bytes[6];
    XYZ<int> readings;
    memset(bytes, 0, 6);

    imu->i2cRead(address, readRegister, 6, bytes);

    for(int i = 0; i < 6; i++) {
      Serial.print(bytes[i]);
      Serial.print(", ");
    }
    Serial.println();

    readings.x = (int)bytes[0] + (((int)bytes[1]) << 8);
    readings.y = (int)bytes[2] + (((int)bytes[3]) << 8);
    readings.z = (int)bytes[4] + (((int)bytes[5]) << 8);

    return readings;
}

/**
 * Zero the data based on our previous values for zero
 */
void IMUSensor::zeroData(XYZ<double>& readings){
    readings.x -= zero.x;
    readings.y -= zero.y;
    readings.z -= zero.z;
}

/**
 * Get sensor reading when quadcopter is perfectly flat and not moving and save as 0 value
 */
void IMUSensor::findZero(){
    double x = 0.0, y = 0.0, z = 0.0;
    for(int i = 0; i < ZERO_SAMPLE_COUNT; ++i){
        XYZ<int>& raw = read();
        Serial.print("findZero: raw.x: ");
        Serial.print(raw.x);
        XYZ<double> converted = convert(raw);
        Serial.print(" findZero: converted.x: ");
        Serial.println(converted.x);
        x += converted.x;
        y += converted.y;
        z += converted.z;
        delay(10);
    }
    
    zero.x = x/ZERO_SAMPLE_COUNT;
    zero.y = y/ZERO_SAMPLE_COUNT;
    zero.z = z/ZERO_SAMPLE_COUNT;
}
