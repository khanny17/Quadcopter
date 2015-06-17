#include <Wire.h>
#include "imu.h"
#include "pid.h"
#include "pryh.h"

imu imu;
pid pitchPID;
pid rollPID;


void setup() {
  Serial.begin(9600);
  imu.setup(); //intialize the IMU unit
}

void loop() {
  if(Serial.available()){
    //TODO read command of some sort
  }
  PRYH actual = getPRYH(); //print out the values in the IMU
  PRYH errors = calcErrors(actual);
  Serial.print("Pitch: ");
  Serial.print(errors.pitch);
  Serial.print(" Roll: ");
  Serial.print(errors.roll);
  Serial.print('\n');
  delay(100);
}

PRYH getPRYH() {
  imu.update();
  int pitch = imu.getPitch();
  int roll = imu.getRoll();
  //Serial.print("pitch: ");
  //Serial.print(pitch);
  //Serial.print(" roll: ");
  //Serial.println(roll);
  
  return (PRYH){pitch, roll, 0, 0};
}

PRYH calcErrors(PRYH actual){
  return (PRYH){
    pitchPID.compute(actual.pitch),
    rollPID.compute(actual.roll),
    0,
    0
  };
}
