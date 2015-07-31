/** 
 *  Module for reading info from the adafruit 9DOF Sensor Stick
 *
 *  Adapted from: http://robotosh.blogspot.com/2012/03/sparkfun-9dof-imu-sensor-stick.html
 */

#include "Arduino.h"
#include "imu.h"
#include "Wire.h"

imu::imu() {
  for(int i = 0; i < 3; ++i) {
    this->accelerometer_data[i] = this->magnetometer_data[i] = this->gyro_data[i] = 0;
  }
}

void imu::init() {
  Wire.begin();
  
  this->init_adxl345();
  this->init_hmc5843();
  this->init_itg3200();
  
  this->buffer(); //fill buffer up
}

/**
 * Prints whatever the current data is
 */
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

/**
 * Returns the accelerometer value for the given axis
 */
float imu::getAccData(int axis){
  return this->acc_buffers[axis].average();
}

/**
 * Returns the gyro value for the given axis
 */
float imu::getGyroData(int axis){
  return this->gyro_buffers[axis].average();
}

/**
 * Gets new data from all the sensors
 */
void imu::update(){
  this->read_adxl345();
  this->read_itg3200();
  this->read_hmc5843();
   
  //Convert to degrees
  this->acc_to_degrees();
  this->gyro_to_degrees_per_sec();

  //Add to the buffers
  this->acc_buffers[0].add(accelerometer_data[0]);
  this->acc_buffers[1].add(accelerometer_data[1]);
  this->acc_buffers[2].add(accelerometer_data[2]);
  
  this->gyro_buffers[0].add(gyro_data[0]);
  this->gyro_buffers[1].add(gyro_data[1]);
  this->gyro_buffers[2].add(gyro_data[2]);
  
  this->mag_buffers[0].add(magnetometer_data[0]);
  this->mag_buffers[1].add(magnetometer_data[1]);
  this->mag_buffers[2].add(magnetometer_data[2]);
 
}

/**
 *  Calls update until buffers are filled
 */
void imu::buffer(){
  int i;
  for(i = 0; i < ACC_BUFFER_SIZE; ++i){ //TODO legitamize this
    this->update();
    /*this->read_adxl345();
   
    //Convert to degrees
    this->acc_to_degrees();

    //Add to the buffers
    this->acc_buffers[0].add(accelerometer_data[0]);
    this->acc_buffers[1].add(accelerometer_data[1]);
    this->acc_buffers[2].add(accelerometer_data[2]);*/
  }
}

/**
 * Converts Accelerometer readings to degrees
 * PRECONDITION: The values in accelerometer_data are not ALREADY in degrees
 */
void imu::acc_to_degrees(){
  float x = this->accelerometer_data[0];
  float y = this->accelerometer_data[1];
  float z = this->accelerometer_data[2];
  
  //57.29578 is 180 / pi
  float xA = tan( x / sqrt( sq(y)+sq(z) ))  * 57.296; 
  float yA = atan( y / sqrt( sq(x)+sq(z) ))  * 57.296;
  float zA = atan( sqrt( sq(y)+sq(x) / z  ))  * 57.296;
  
  this->accelerometer_data[0] = xA;
  this->accelerometer_data[1] = yA;
  this->accelerometer_data[2] = zA;
}

/**
 *  Converts gyro reading to degrees/sec
 */
void imu::gyro_to_degrees_per_sec(){
  int i; 
  for(i = 0; i < 3; ++i){
    gyro_data[i] = gyro_data[i] / 14.7;
  }
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
