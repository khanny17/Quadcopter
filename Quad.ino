#include <Wire.h>
#include <Servo.h>
#include <NewPing.h>
#include "imu.h"
#include "pid.h"
#include "pry.h"
#include "sensors.h"
#include "motors.h"
#include "controller.h"


#define FRONT_PIN 4 //TODO config this
#define LEFT_PIN  5
#define BACK_PIN  6
#define RIGHT_PIN 7

SensorInterface sensors;
MotorController motors;
Controller ctrl;

int start; //the time "setup" ends

void setup() {
  //Serial.begin(9600);
  sensors.init();
  motors.init(FRONT_PIN, LEFT_PIN, BACK_PIN, RIGHT_PIN);

  //TODO wait for configurations over serial?
  
  ctrl.setDesiredHeight(100); //100cm = 1m
  start = millis();
}

void loop() {
  //if(Serial.available()){
    //TODO read command of some sort from raspi
  //} 
  
  //Get current sensor readings
  PRY actualPry = sensors.getPRY(); 
  int height = sensors.getHeight();
  //int vertVelocity = sensors.getVerticalVelocity();
  //Serial.print("VertVelocity: "); Serial.print(vertVelocity); Serial.print("\n");

  //Calculate errors
  PRY errorsPry = ctrl.calcPryErrors(actualPry); //Calculate error from where we want to be
  int heightError = ctrl.calcHeightError(height);

  //Serial.print("heightError: "); Serial.print(heightError); Serial.print("\n");
  //int vertVelocityError = ctrl.calcVerticalVelocityError(vertVelocity, heightError);


  //Adjust motor speeds
  motors.adjustSpeeds(errorsPry, heightError); //Adjust motor speeds based on the errors

  
  //motors.printSpeeds();

  if(millis() - start > 3000){ //after 3 seconds, shut it down
    while(true){
      motors.sendLow();
    }
  }
  
}



