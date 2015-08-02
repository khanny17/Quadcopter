#include "Motors.h"

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

void MotorController::sendHigh(){
   this->front.writeMicroseconds(MOTOR_MAX);
   this->left.writeMicroseconds(MOTOR_MAX);
   this->back.writeMicroseconds(MOTOR_MAX);
   this->right.writeMicroseconds(MOTOR_MAX);
}

void MotorController::sendLow(){
   this->front.writeMicroseconds(MOTOR_OFF);
   this->left.writeMicroseconds(MOTOR_OFF);
   this->back.writeMicroseconds(MOTOR_OFF);
   this->right.writeMicroseconds(MOTOR_OFF);
}

int F, L, B, R, i, T; //temp variables
void MotorController::adjustSpeeds(PRY corrections, int heightError){
  //Get combined error for each motor
  F = (corrections.pitch+corrections.yaw);
  L = (corrections.roll-corrections.yaw);
  B = (-corrections.pitch+corrections.yaw);
  R = (-corrections.roll-corrections.yaw);

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
  this->front.writeMicroseconds(constrain(this->frontSpd, MOTOR_MIN, MOTOR_MAX));
  //this->left.writeMicroseconds(constrain(this->leftSpd, MOTOR_MIN, MOTOR_MAX));
  this->back.writeMicroseconds(constrain(this->backSpd, MOTOR_MIN, MOTOR_MAX));
  //this->right.writeMicroseconds(constrain(this->rightSpd, MOTOR_MIN, MOTOR_MAX));
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
