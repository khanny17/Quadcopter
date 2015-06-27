#include <Wire.h>
#include <Servo.h>
#include "imu.h"
#include "pid.h"
#include "pry.h"
#include "sensors.h"
#include "motors.h"
#include "controller.h"


#define FRONT_PIN 6 //TODO config this
#define LEFT_PIN  9
#define BACK_PIN  10
#define RIGHT_PIN 11

SensorInterface sensors;
MotorController motors;
Controller ctrl;


void setup() {
  Serial.begin(9600);
  sensors.init();
  motors.init(FRONT_PIN, LEFT_PIN, BACK_PIN, RIGHT_PIN);
  ctrl.setDesiredHeight(100); //100cm = 1m
}

void loop() {
  //if(Serial.available()){
    //TODO read command of some sort from raspi
  //}
  
  //Get current sensor readings
  PRY actualPry = sensors.getPRY(); 
  int height = sensors.getHeight();
  int vertVelocity = sensors.getVerticalVelocity();
  
  PRY errorsPry = ctrl.calcPryErrors(actualPry); //Calculate error from where we want to be
  int heightError = ctrl.calcHeightError(height);
  int vertVelocityError = ctrl.calcVerticalVelocityError(vertVelocity, heightError);
  
  motors.adjustSpeeds(errorsPry, vertVelocityError); //Adjust motor speeds based on the errors
  motors.printSpeeds();
  
  delay(100);
}



