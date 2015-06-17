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
    //TODO read command of some sort from raspi
  }
  PRYH actual = sensors.getPRYH(); //Get current sensor readings
  PRYH errors = calcErrors(actual); //Calculate error from where we want to be
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
