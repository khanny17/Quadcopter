#include <Wire.h>
#include <Servo.h>
#include <NewPing.h>
#include "IMU.h"
#include "PID.h"
#include "Sensors.h"
#include "Motors.h"
#include "Controller.h"
#include "Command.h"


#define FRONT_PIN 6 //TODO config this
#define LEFT_PIN  4
#define BACK_PIN  5
#define RIGHT_PIN 7

SensorInterface sensors;
MotorController motors;
Controller ctrl;
CommandHandler command;

void initializeMotors();
void initializeSensors();
void initializeController();


int start;              //the time "setup" ends


void setup() {
  Serial.begin(9600);
  delay(2000);
  
  Serial.println("Enter \"C\" to start configuration");
  while(command.readNewCommand() != CONFIGURE); //wait for configuration command
  
  initializeMotors();
  initializeSensors(); // Initialize AFTER the motors. The ten second delay causes issues for measurements
  initializeController();
  

  Serial.println("Configuration Complete");
  
  start = millis();
}

//unsigned long prev; //used for debugging
//float P,I,D;


void loop() {
  
  //prev = millis();

  command.readNewCommand();
  
  switch(command.getCurrentCommand()){
    case RUN:   run();
                break;
                
    case STOP:  stop();
                break;
                
    case RESET: reset();
                break;
                
    default:    break; 
  }
}

void initializeMotors(){
  Serial.println("Initializing Motors");
  motors.init(FRONT_PIN, LEFT_PIN, BACK_PIN, RIGHT_PIN);
  Serial.println("Motors Initialized");
}

void initializeSensors(){
  Serial.println("Initializing Sensors");
  sensors.init();
  Serial.println("Sensors Initialized");
}

void initializeController(){
  Serial.println("Initializing Controller");
  ctrl.setDesiredHeight(100); //100cm = 1m
  Serial.println("Controller Initialized");
}

/**
 *  Runs the normal balancing algorithm:
 *   update sensors, calculate correction, update motors
 */
void run(){
  //Get current sensor readings
  //PRY actualPry = sensors.getPRY();
  //Serial.print("Reading: "); Serial.print(actualPry.pitch); Serial.print('\n');
  
  //Calculate corrections
  //PRY correctionPry = ctrl.calcPryCorrection(actualPry);
  
  //Adjust motor speeds
  //motors.adjustSpeeds(correctionPry, 0); //Update motor with correction
}

/**
 * Continuously send off signal to motors
 */
void stop(){
  motors.sendLow();
  ctrl.reset();
}

/**
 *  Stop motors, run setup again, set command to the stop command
 */
void reset(){
  stop();
  setup();        
  command.setCurrentCommand((Command)STOP);
}
