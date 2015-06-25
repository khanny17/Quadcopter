#include <Wire.h>
#include <Servo.h>
#include "imu.h"
#include "pid.h"
#include "pryh.h"
#include "sensors.h"
#include "motors.h"


#define FRONT_PIN 6 //TODO config this
#define LEFT_PIN  9
#define BACK_PIN  10
#define RIGHT_PIN 11

SensorInterface sensors;
MotorController motors;

pid pitchPID(1, 0, 1);
pid rollPID(1, 0, 1); //TODO config this
//pid yawPID;
pid heightPID(1, .5, .5);


void setup() {
  Serial.begin(9600);
  sensors.init();
  motors.init(FRONT_PIN, LEFT_PIN, BACK_PIN, RIGHT_PIN);
}

void loop() {
  //if(Serial.available()){
    //TODO read command of some sort from raspi
  //}
  PRYH actual = sensors.getPRYH(); //Get current sensor readings
  PRYH errors = calcErrors(actual); //Calculate error from where we want to be
  motors.adjustSpeeds(errors); //Adjust motor speeds based on the error
  motors.printSpeeds();
  
  delay(100);
}

PRYH calcErrors(PRYH actual){
  return (PRYH){
    pitchPID.compute(actual.pitch),
    rollPID.compute(actual.roll),
    0, //TODO implement yaw!
    heightPID.compute(actual.height)
  };
}
