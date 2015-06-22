#include "Arduino.h"
#include "motors.h"
#include "Servo.h"
#include "pryh.h"

/**
 *  Connects Motors to the specified pins
 */
MotorController::MotorController(int f, int l, int b, int r){
   this->front.attach(f);
   this->left.attach(l);
   this->back.attach(b);
   this->right.attach(r);
   this->speeds[0] = MOTOR_OFF;
   this->speeds[1] = MOTOR_OFF;
   this->speeds[2] = MOTOR_OFF;
   this->speeds[3] = MOTOR_OFF;
   this->writeSpeeds();
}
int F, L, B, R, i; //temp variables
void MotorController::adjustSpeeds(PRYH errors){
  
  
  //Get combined error for each motor
  F = (-errors.pitch+errors.yaw);
  L = (-errors.roll-errors.yaw);
  B = (errors.pitch+errors.yaw);
  R = (errors.roll-errors.yaw);
  
  //Use error to determine amound to increase/decrease motor speeds by
  F = map(F, -560, 560, -MAX_INCREMENT, MAX_INCREMENT);
  L = map(L, -560, 560, -MAX_INCREMENT, MAX_INCREMENT);
  B = map(B, -560, 560, -MAX_INCREMENT, MAX_INCREMENT);
  R = map(R, -560, 560, -MAX_INCREMENT, MAX_INCREMENT);
  
  //set new speeds
  this->speeds[0] = this->speeds[0]+F;
  this->speeds[1] = this->speeds[1]+L;
  this->speeds[2] = this->speeds[2]+B;
  this->speeds[3] = this->speeds[3]+R;
  
  //Check we are within bounds
  for(i = 0; i < 4; ++i){
    if(this->speeds[i] > MOTOR_MAX){
      this->speeds[i] = MOTOR_MAX;
    } else if(this->speeds[i] < MOTOR_MIN){
      this->speeds[i] = MOTOR_MIN;
    }
  }
  
  //write new speeds
  this->writeSpeeds();
}

void MotorController::writeSpeeds(){
  this->front.write(this->speeds[0]);
  this->left.write(this->speeds[1]);
  this->back.write(this->speeds[2]);
  this->right.write(this->speeds[3]);
}
