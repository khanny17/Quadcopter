#include <Wire.h>
#include <Servo.h>
#include <NewPing.h>
#include "IMU.h"
#include "PID.h"
#include "AttitudeDeterminator.h"
#include "Motors.h"
#include "Controller.h"
#include "Command.h"


#define FRONT_PIN 6 //TODO config this
#define LEFT_PIN  4
#define BACK_PIN  5
#define RIGHT_PIN 7

AttitudeDeterminator* attitude;
MotorController* motors;
Controller* ctrl;
CommandHandler* command;

void initializeMotors();
void initializeSensors();
void initializeController();


int start;              //the time "setup" ends


void setup() {
  initializeCommunications();
  
  Serial.println("Enter \"C\" to start configuration");
  while(command->readNewCommand() != CONFIGURE); //wait for configuration command
  
  motors = new MotorController(FRONT_PIN, LEFT_PIN, BACK_PIN, RIGHT_PIN);
  attitude = new AttitudeDeterminator(0);
  ctrl = new Controller;
  

  Serial.println("Configuration Complete");
  
  start = millis();
}


void loop() {

  command->readNewCommand();
  
  switch(command->getCurrentCommand()){
    case RUN:   run();
                break;
                
    case STOP:  stop();
                break;
                
    case RESET: reset();
                break;
                
    default:    break; 
  }
}

/**
 * Start communications over usb from arduino to user
 */
void initializeCommunications(){
  Serial.begin(9600);
  delay(2000);
  CommandHandler c;
  command = &c;
  Serial.println("Communications Initialized");
}

/**
 *  Runs the normal balancing algorithm:
 *   update sensors, calculate correction, update motors
 */
float pitch, roll, yaw;
void run(){
  //Get current sensor readings
  attitude->getAttitude(&pitch, &roll, &yaw);
  Serial.print("Reading: "); Serial.print(pitch); Serial.print('\n');
  
  //Calculate corrections
  //PRY correctionPry = ctrl.calcPryCorrection(actualPry);
  
  //Adjust motor speeds
  //motors.adjustSpeeds(correctionPry, 0); //Update motor with correction
}

/**
 * Continuously send off signal to motors
 */
void stop(){
  motors->sendLow();
  ctrl->reset();
}

/**
 *  Stop motors, run setup again, set command to the stop command
 */
void reset(){
  stop();
  setup();        
  command->setCurrentCommand((Command)STOP);
}
