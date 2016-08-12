/** 
 *  Module for reading info from the adafruit 9DOF Sensor Stick
 *
 *  Adapted from: http://robotosh.blogspot.com/2012/03/sparkfun-9dof-imu-sensor-stick.html
 */

#include "IMU.h"

IMU::IMU(){
  //Wire.begin();
}

void IMU::i2cWrite(int address, char reg, char data) {
  //Wire.beginTransmission(address);
  //Wire.write(reg);
  //Wire.write(data);
  //Wire.endTransmission();
}

void IMU::i2cRead(int address, char reg, int count, char *data) {
  //int i = 0;
  //char c;
  //
  //Wire.beginTransmission(address);
  //Wire.write(reg);
  //Wire.endTransmission();
  //Wire.beginTransmission(address);
  //Wire.requestFrom(address,count);
  //while(Wire.available()){
  //  c = Wire.read();
  //  data[i] = c;
  //  i++;
  //}
  //Wire.endTransmission();
} 
