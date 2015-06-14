#include <Wire.h>
#include "imu.h"

imu imu;

void setup() {
  Serial.begin(9600);
  imu.setup(); //intialize the IMU unit
}

void loop() {
  imu.update(); //read new values from the IMU
  imu.prettyPrint(); //print out the values in the IMU
  delay(100);
}
