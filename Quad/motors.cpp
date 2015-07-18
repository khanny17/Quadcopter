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
   delay(10000); //Wait five seconds to make sure the motors read it
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
  L = (-errors.roll-errors.yaw);
  B = (-errors.pitch+errors.yaw);
  R = (errors.roll-errors.yaw);

  
  //Use error to determine amound to increase/decrease motor speeds by
  //TODO define the min and max errors elsewhere
  F = map(F, -MAX_DEGREE_ERROR, MAX_DEGREE_ERROR, -OFFSET, OFFSET);
  L = map(L, -MAX_DEGREE_ERROR, MAX_DEGREE_ERROR, -OFFSET, OFFSET);
  B = map(B, -MAX_DEGREE_ERROR, MAX_DEGREE_ERROR, -OFFSET, OFFSET);
  R = map(R, -MAX_DEGREE_ERROR, MAX_DEGREE_ERROR, -OFFSET, OFFSET);

  //Calculate the base throttle based on error in desired speed
  //TODO play with the numbers here. this maps 1m to 20
  T = map(heightError, -100, 100, -THROTTLE_INCREMENT, THROTTLE_INCREMENT);
  this->throttle = constrain(this->throttle+T, MIN_THROTTLE, MAX_THROTTLE);
  
  // Set new speeds, keeping them within max and min bounds
  this->frontSpd = constrain(this->throttle+F, MOTOR_MIN, MOTOR_MAX);
  this->leftSpd = constrain(this->throttle+L, MOTOR_MIN, MOTOR_MAX);;
  this->backSpd = constrain(this->throttle+B, MOTOR_MIN, MOTOR_MAX);;
  this->rightSpd = constrain(this->throttle+R, MOTOR_MIN, MOTOR_MAX);;
  
  //write new speeds
  this->writeSpeeds();
}

/**
 *  PRECONDITION: the speeds are kept in the proper range so we dont write an invalid speed
 */
void MotorController::writeSpeeds(){
  this->front.write(this->frontSpd);
  this->left.write(this->leftSpd);
  this->back.write(this->backSpd);
  this->right.write(this->rightSpd);
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
