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

void initializeMotors();
void initializeSensors();
void initializeController();

int start;          //the time "setup" ends
char command = 'S'; //the latest command received from serial - default is S, or stop

void setup() {
  Serial.begin(9600);
  delay(2000);
  
  Serial.println("Enter \"C\" to start configuration");
  while((char)Serial.read() != 'C'); //wait for input
  
  initializeMotors();
  initializeSensors(); // Initialize AFTER the motors. The ten second delay causes issues for measurements
  initializeController();
  
  
  //TODO wait for configurations over serial?  
  Serial.println("Configuration Complete");
  
  start = millis();
}

unsigned long prev; //used for debugging
float P,I,D;


void loop() {
  
  prev = millis();

  //check for new command
  if(Serial.available()){
    command = (char)Serial.read();
    
    Serial.println(command);
  } 
  
  if(command == 'G'){ //G for "Go"
  
  
    //Get current sensor readings
    PRY actualPry = sensors.getPRY();
    Serial.print("Reading: "); Serial.print(actualPry.pitch); Serial.print('\n');
    
    //Calculate corrections
    PRY correctionPry = ctrl.calcPryCorrection(actualPry);
    //Serial.print("Correction: "); Serial.print(correctionPry.pitch); Serial.print('\n');
  
    //Adjust motor speeds
    motors.adjustSpeeds(correctionPry, 0); //Update motor with correction
  
    //motors.printSpeeds();
    
    
  } else if(command == 'S'){ //S means stop
    motors.sendLow();
  } else if(command == 'R'){ //R means Reset - stop motors, run setup, set command to "S"
    motors.sendLow();
    setup();        
    command = 'S';
  } else if(command == 'P'){ //TODO this is debug code
      P = Serial.parseFloat(); 
      Serial.read(); //skip comma
      I = Serial.parseFloat();
      Serial.read();
      D = Serial.parseFloat();
      
      ctrl.setPitchPIDGains(P,I,D);
      Serial.println(P);
      Serial.println(I);
      Serial.println(D);
      command = 'G';
    }
}


void initializeMotors(){
  Serial.println("Initializing Motors");
  motors.init(FRONT_PIN, LEFT_PIN, BACK_PIN, RIGHT_PIN);
  Serial.println("Motors Initialized");
}

void initializeSensors(){
  Serial.println("Initializing Sensors");
  sensors.init(K_G_P);
  Serial.println("Sensors Initialized");
}

void initializeController(){
  Serial.println("Initializing Controller");
  ctrl.setDesiredHeight(100); //100cm = 1m
  Serial.println("Controller Initialized");
}
