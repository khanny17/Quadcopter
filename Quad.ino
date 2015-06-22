#include <Wire.h>
#include <Servo.h>
#include "imu.h"
#include "pid.h"
#include "pryh.h"
#include "sensors.h"
#include "motors.h"


SensorInterface sensors;
MotorController motors(6,9,10,11);

pid pitchPID;
pid rollPID;


void setup() {
  Serial.begin(9600);
}

void loop() {
  //if(Serial.available()){
    //TODO read command of some sort from raspi
  //}
  PRYH actual = sensors.getPRYH(); //Get current sensor readings
  Serial.print("Actual Pitch: ");
  Serial.print(actual.pitch);
  Serial.print("\n");
  Serial.print("Actual Roll: ");
  Serial.print(actual.roll);
  Serial.print("\n");
  PRYH errors = calcErrors(actual); //Calculate error from where we want to be
  Serial.print("Error Pitch: ");
  Serial.print(errors.pitch);
  Serial.print("\n");
  Serial.print("Error Roll: ");
  Serial.print(errors.roll);
  Serial.print("\n");
  motors.adjustSpeeds(errors);
  
  delay(1000);
}

PRYH calcErrors(PRYH actual){
  return (PRYH){
    pitchPID.compute(actual.pitch),
    rollPID.compute(actual.roll),
    0,
    0
  };
}
