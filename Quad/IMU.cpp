#include "IMU.h"

IMU::IMU() {
    Wire.begin();
}

void IMU::i2c_write(int address, byte reg, byte data) {
    // Send output register address
    Wire.beginTransmission(address);
    Wire.write(reg);
    // Connect to device and send byte
    Wire.write(data); // low byte
    Wire.endTransmission();
}

void IMU::i2c_read(int address, byte reg, int count, byte* data) {
   int i = 0;
  
   // Send input register address
   Wire.beginTransmission(address);
   Wire.write(reg);
   Wire.endTransmission();
   // Connect to device and request bytes
   Wire.beginTransmission(address);
   Wire.requestFrom(address,count);
   while(Wire.available()) { // slave may send less than requested
       char c = Wire.read(); // receive a byte as character
       data[i] = c;
       i++;
   }
   Wire.endTransmission();
}

void IMU::init_adxl345() {
    byte data = 0;
    i2c_write(ADXL345_ADDRESS, ADXL_REGISTER_PWRCTL, ADXL_PWRCTL_MEASURE);
  
    //Check to see if it worked!
    i2c_read(ADXL345_ADDRESS, ADXL_REGISTER_PWRCTL, 1, &data);
    Serial.print("adxl345 register value: ");
    Serial.println((unsigned int)data, BIN);
}

void IMU::read_adxl345() {
    byte bytes[6];
    memset(bytes,0,6);
    
    //read 6 bytes from the ADXL345
    i2c_read(ADXL345_ADDRESS, ADXL345_REGISTER_XLSB, 6, bytes);
    
    //now unpack the bytes
    accelerometer_data.x = (int)bytes[0] + (((int)bytes[1]) << 8);
    accelerometer_data.y = (int)bytes[2] + (((int)bytes[3]) << 8);
    accelerometer_data.z = (int)bytes[4] + (((int)bytes[5]) << 8);
    //Serial.print("Accelerometer Data:");
    //Util::print_xyz(accelerometer_data);
}

void IMU::init_itg3200() {
    byte data = 0;
  
    //Set DLPF to 42 Hz (change it if you want) and
    //set the scale to "Full Scale"
    i2c_write(ITG3200_ADDRESS, ITG3200_REGISTER_DLPF_FS, ITG3200_FULLSCALE | ITG3200_42HZ);
  
    //Sanity check! Make sure the register value is correct.
    i2c_read(ITG3200_ADDRESS, ITG3200_REGISTER_DLPF_FS, 1, &data);
    Serial.print("itg3200 register value: ");
    Serial.println((unsigned int)data, BIN);
}

void IMU::read_itg3200() {
    byte bytes[6];
    memset(bytes,0,6);
    
    //read 6 bytes from the ITG3200
    i2c_read(ITG3200_ADDRESS, ITG3200_REGISTER_XMSB, 6, bytes);  //now unpack the bytes

    //now unpack the bytes
    gyro_data.x = (int)bytes[1] + (((int)bytes[0]) << 8);
    gyro_data.y = (int)bytes[3] + (((int)bytes[2]) << 8);
    gyro_data.z = (int)bytes[5] + (((int)bytes[4]) << 8);
}

void IMU::init_hmc5843() {
    byte data = 0;
    //set up continuous measurement
    i2c_write(HMC5843_ADDRESS, HMC5843_REGISTER_MEASMODE, HMC5843_MEASMODE_CONT);
    
    //Sanity check, make sure the register value is correct.
    i2c_read(HMC5843_ADDRESS, HMC5843_REGISTER_MEASMODE, 1, &data);
    Serial.print("hmc5843 register value: ");
    Serial.println((unsigned int)data, BIN);
}

void IMU::read_hmc5843() {
    byte bytes[6];
    memset(bytes,0,6);
    
    //read 6 bytes from the HMC5843
    i2c_read(HMC5843_ADDRESS, HMC5843_REGISTER_XMSB, 6, bytes);

    //now unpack the bytes
    magnetometer_data.x = (int)bytes[1] + (((int)bytes[0]) << 8);
    magnetometer_data.y = (int)bytes[3] + (((int)bytes[2]) << 8);
    magnetometer_data.z = (int)bytes[5] + (((int)bytes[4]) << 8);
}

XYZ<int> IMU::get_accelerometer_data() {
    return accelerometer_data;
}

XYZ<int> IMU::get_gyroscope_data() {
    return gyro_data;
}

XYZ<int> IMU::get_magnetometer_data() {
    return magnetometer_data;
}
        
