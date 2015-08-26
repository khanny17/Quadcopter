#include <Wire.h>
#include <Servo.h>
#include <NewPing.h>
#include "AttitudeDeterminator.h"
#include "Motors.h"
#include "Controller.h"


#define FRONT_PIN 6 //TODO config this
#define LEFT_PIN  4
#define BACK_PIN  5
#define RIGHT_PIN 7

AttitudeDeterminator* attitude;
MotorController* motors;
Controller* ctrl;

float pitch, roll, yaw;
int pitchCorrection, rollCorrection, yawCorrection;

void setup() {
  Serial.begin(9600);
  
  motors = new MotorController(FRONT_PIN, LEFT_PIN, BACK_PIN, RIGHT_PIN);
  attitude = new AttitudeDeterminator(0);
  ctrl = new Controller;
  

  Serial.println("Configuration Complete");
}

char c = 'S';
void loop() {
  if(Serial.available()){
    c = (char)Serial.read();
  }
  if(c == 'G'){
    //Get current sensor readings
    attitude->getAttitude(&pitch, &roll, &yaw);
    Serial.print("Reading: "); Serial.print(pitch); Serial.print('\n');
    
    //Calculate corrections
    ctrl->calcPryCorrection(pitch, roll, yaw, &pitchCorrection, &rollCorrection, &yawCorrection);
    
    //Adjust motor speeds
    motors->adjustSpeeds(pitchCorrection, rollCorrection, yawCorrection, 0); //Update motor with correction
  } else {
    motors->sendLow();
  }
}
