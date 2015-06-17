#include <Wire.h>
#include "imu.h"
#include "pid.h"
#include "pryh.h"
#include "sensors.h"


SensorInterface sensors;

pid pitchPID;
pid rollPID;


void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    //TODO read command of some sort
  }
  PRYH actual = sensors.getPRYH(); //print out the values in the IMU
  PRYH errors = calcErrors(actual);
  Serial.print("Pitch: ");
  Serial.print(errors.pitch);
  Serial.print(" Roll: ");
  Serial.print(errors.roll);
  Serial.print('\n');
  delay(100);
}

PRYH calcErrors(PRYH actual){
  return (PRYH){
    pitchPID.compute(actual.pitch),
    rollPID.compute(actual.roll),
    0,
    0
  };
}
