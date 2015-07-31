#include <Wire.h>
#include <Servo.h>
#include <NewPing.h>
#include "imu.h"
#include "pid.h"
#include "pry.h"
#include "sensors.h"
#include "motors.h"
#include "controller.h"


#define FRONT_PIN 6 //TODO config this
#define LEFT_PIN  4
#define BACK_PIN  5
#define RIGHT_PIN 7

#define K_G_P .02 //the ratio of gyro to accelerometer usage in pitch calculation

SensorInterface sensors;
MotorController motors;
Controller ctrl;

int start;          //the time "setup" ends
char command = 'S'; //the latest command received from serial - default is S, or stop

void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("Enter \"C\" to start configuration");
  while((char)Serial.read() != 'C');
  motors.init(FRONT_PIN, LEFT_PIN, BACK_PIN, RIGHT_PIN);
  Serial.println("Motors initialized");
  sensors.init(K_G_P);// Initialize AFTER the motors. The ten second delay causes issues for measurements
  Serial.println("Sensors Initialized");

  //TODO wait for configurations over serial?
  
  ctrl.setDesiredHeight(100); //100cm = 1m
  Serial.println("Controller Initialized");
  
  Serial.println("Configuration Complete");
  start = millis();
}

unsigned long prev;

void loop() {
  
  prev = millis();

  if(Serial.available()){
    command = (char)Serial.read();
    Serial.println(command);
  } 
  
  if(command == 'G'){ //G for "Go"
    //Get current sensor readings
    PRY actualPry = sensors.getPRY();
    //Serial.println(millis() - prev);
    //int height = sensors.getHeight();
    //int vertVelocity = sensors.getVerticalVelocity();
    //Serial.print("VertVelocity: "); Serial.print(vertVelocity); Serial.print("\n");
    Serial.print("Reading: "); Serial.print(actualPry.pitch); Serial.print('\n');
    //Calculate errors
    PRY correctionPry = ctrl.calcPryCorrection(actualPry); //Calculate error from where we want to be
    
    
    //int heightError = ctrl.calcHeightError(height);
  
    //Serial.print("heightError: "); Serial.print(heightError); Serial.print("\n");
    //int vertVelocityError = ctrl.calcVerticalVelocityError(vertVelocity, heightError);
    //Serial.println(errorsPry.pitch);
    //Serial.print("Correction: "); Serial.print(correctionPry.pitch); Serial.print('\n');
  
    //Adjust motor speeds
    //motors.adjustSpeeds(correctionPry, heightError); //Adjust motor speeds based on the errors
    motors.adjustSpeeds(correctionPry, 0); //Adjust motor speeds based on the errors
  
    
    //motors.printSpeeds();
    //Serial.println("");
    
  } else if(command == 'S'){ //S means stop
    motors.sendLow();
  } else if(command == 'R'){ //R means Reset - stop motors, run setup, set command to "S"
    motors.sendLow();
    setup();        
    command = 'S';
  }
  
  //Serial.println(millis() - prev);
}



