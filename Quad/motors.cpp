#include "Arduino.h"
#include "motors.h"
#include "pry.h"

MotorController::MotorController(){
  
}

/**
 *  Connects Motors to the specified pins
 */
void MotorController::init(int f, int l, int b, int r){
   this->front.attach(f);
   this->left.attach(l);
   this->back.attach(b);
   this->right.attach(r);
   this->sendLow(); //To initialize the motors, they need to receive a low signal
   delay(10000); //Wait ten seconds to make sure the motors read it
}

void MotorController::sendLow(){
   this->front.write(MOTOR_OFF);
   this->left.write(MOTOR_OFF);
   this->back.write(MOTOR_OFF);
   this->right.write(MOTOR_OFF);
}

int F, L, B, R, i, T; //temp variables
void MotorController::adjustSpeeds(PRY errors, int heightError){
  //Get combined error for each motor
  F = (errors.pitch+errors.yaw);
  L = (errors.roll-errors.yaw);
  B = (-errors.pitch+errors.yaw);
  R = (-errors.roll-errors.yaw);

  
  //Use error to determine amound to increase/decrease motor speeds by
  /*
  F = map(F, -MAX_DEGREE_ERROR, MAX_DEGREE_ERROR, -OFFSET, OFFSET);
  L = map(L, -MAX_DEGREE_ERROR, MAX_DEGREE_ERROR, -OFFSET, OFFSET);
  B = map(B, -MAX_DEGREE_ERROR, MAX_DEGREE_ERROR, -OFFSET, OFFSET);
  R = map(R, -MAX_DEGREE_ERROR, MAX_DEGREE_ERROR, -OFFSET, OFFSET);
  */
  
  F = constrain(F, -OFFSET, OFFSET);
  L = constrain(L, -OFFSET, OFFSET);
  B = constrain(B, -OFFSET, OFFSET);
  R = constrain(R, -OFFSET, OFFSET);

  //Calculate the base throttle based on error in desired speed
  T = map(heightError, -100, 100, -THROTTLE_INCREMENT, THROTTLE_INCREMENT);
  this->throttle = constrain(this->throttle+T, MIN_THROTTLE, MAX_THROTTLE);
  
  // Set new speeds
  this->frontSpd = this->throttle+F;
  this->leftSpd = this->throttle+L;
  this->backSpd = this->throttle+B;
  this->rightSpd = this->throttle+R;
  
  //write new speeds
  this->writeSpeeds();
}

/**
 *  Constrains speeds and writes them out
 */
void MotorController::writeSpeeds(){
  this->front.write(constrain(this->frontSpd, MOTOR_MIN, MOTOR_MAX));
  //this->left.write(constrain(this->leftSpd, MOTOR_MIN, MOTOR_MAX));
  this->back.write(constrain(this->backSpd, MOTOR_MIN, MOTOR_MAX));
  //this->right.write(constrain(this->rightSpd, MOTOR_MIN, MOTOR_MAX));
}

void MotorController::printSpeeds(){
  Serial.print("Front: ");
  Serial.print(this->frontSpd);
  Serial.print("     Left: ");
  Serial.print(this->leftSpd);
  Serial.print("     Back: ");
  Serial.print(this->backSpd);
  Serial.print("     Right: ");
  Serial.print(this->rightSpd);
  Serial.print("\n");
}
