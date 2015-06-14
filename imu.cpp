#include "Arduino.h"
#include "imu.h"
#include "Wire.h"

imu::imu() {
  for(int i = 0; i < 3; ++i) {
    this->accelerometer_data[i] = this->magnetometer_data[i] = this->gyro_data[i] = 0;
  }
  
  
}

void imu::setup() {
  Wire.begin();
  
  this->init_adxl345();
  this->init_hmc5843();
  this->init_itg3200();
}

void imu::prettyPrint() {
   Serial.print("ACCEL: ");
   Serial.print(this->accelerometer_data[0]);
   Serial.print("\t");
   Serial.print(this->accelerometer_data[1]);
   Serial.print("\t");
   Serial.print(this->accelerometer_data[2]);
   Serial.print("\t");
   
   Serial.print("MAG: ");
   Serial.print(this->magnetometer_data[0]);
   Serial.print(",");
   Serial.print(this->magnetometer_data[1]);
   Serial.print(",");
   Serial.print(this->magnetometer_data[2]);
   Serial.print("\t");
   
   Serial.print("GYRO: ");
   Serial.print(this->gyro_data[0]);
   Serial.print("\t");
   Serial.print(this->gyro_data[1]);
   Serial.print("\t");
   Serial.print(this->gyro_data[2]);
   Serial.print("\n");
}

void imu::update(){
  this->read();
}

/**
 *  Reads in the raw data from the IMU
 */
void imu::read() {
   this->read_adxl345();
   this->read_hmc5843();
   this->read_itg3200();
}

void imu::i2c_write(int address, byte reg, byte data) {
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

void imu::i2c_read(int address, byte reg, int count, byte* data) {
 int i = 0;

 Wire.beginTransmission(address);
 Wire.write(reg);
 Wire.endTransmission();
 Wire.beginTransmission(address);
 Wire.requestFrom(address,count);
 while(Wire.available()){
   c = Wire.read();
   data[i] = c;
   i++;
 }
 Wire.endTransmission();
} 

void imu::init_adxl345() {
  byte data = 0;

  this->i2c_write(ADXL345_ADDRESS, ADXL_REGISTER_PWRCTL, ADXL_PWRCTL_MEASURE);

  this->i2c_read(ADXL345_ADDRESS, ADXL_REGISTER_PWRCTL, 1, &data);
  //Serial.println((unsigned int)data);
}


void imu::read_adxl345() {
 byte bytes[6];
 memset(bytes,0,6);

 this->i2c_read(ADXL345_ADDRESS, ADXL345_REGISTER_XLSB, 6, bytes);

 for (int i=0;i<3;++i) {
   this->accelerometer_data[i] = (int)bytes[2*i] + (((int)bytes[2*i + 1]) << 8);
 }
}

void imu::init_itg3200() {
  byte data = 0;

  this->i2c_write(ITG3200_ADDRESS, ITG3200_REGISTER_DLPF_FS, ITG3200_FULLSCALE | ITG3200_42HZ);

  this->i2c_read(ITG3200_ADDRESS, ITG3200_REGISTER_DLPF_FS, 1, &data);

  //Serial.println((unsigned int)data);
}

void imu::read_itg3200() {
  byte bytes[6];
  memset(bytes,0,6);

  this->i2c_read(ITG3200_ADDRESS, ITG3200_REGISTER_XMSB, 6, bytes);
  for (int i=0;i<3;++i) {
    this->gyro_data[i] = (int)bytes[2*i + 1] + (((int)bytes[2*i]) << 8);
  }
}

void imu::init_hmc5843() {
  byte data = 0;
  
  this->i2c_write(HMC5843_ADDRESS, HMC5843_REGISTER_MEASMODE, HMC5843_MEASMODE_CONT);

  this->i2c_read(HMC5843_ADDRESS, HMC5843_REGISTER_MEASMODE, 1, &data);
  //Serial.println((unsigned int)data);
}

void imu::read_hmc5843() {
 byte bytes[6];
 memset(bytes,0,6);

 this->i2c_read(HMC5843_ADDRESS, HMC5843_REGISTER_XMSB, 6, bytes);

 for (int i=0;i<3;++i) {
   this->magnetometer_data[i] = (int)bytes[2*i + 1] + (((int)bytes[2*i]) << 8);
 }
}