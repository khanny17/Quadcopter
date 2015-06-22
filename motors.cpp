#include "Arduino.h"
#include "motors.h"
#include "pryh.h"

/**
 *  Connects Motors to the specified pins
 */
MotorController::MotorController(int f, int l, int b, int r){
   this->front.attach(f);
   this->left.attach(l);
   this->back.attach(b);
   this->right.attach(r);
}

void MotorController::sendLow(){
  int val = 70;
   this->front.write(val);
   this->left.write(val);
   this->back.write(val);
   this->right.write(val);
   delay(2000);
}

int F, L, B, R, i; //temp variables
void MotorController::adjustSpeeds(PRYH errors){
  //Get combined error for each motor
  F = (errors.pitch+errors.yaw);
  L = (-errors.roll-errors.yaw);
  B = (-errors.pitch+errors.yaw);
  R = (errors.roll-errors.yaw);
  
  /*
  Serial.print("F Error: ");
  Serial.print(F);
  Serial.print("     L Error: ");
  Serial.print(L);
  Serial.print("     B Error: ");
  Serial.print(B);
  Serial.print("     R Error: ");
  Serial.print(R);
  Serial.print("\n");
  */
  
  //Use error to determine amound to increase/decrease motor speeds by
  F = map(F, -560, 560, -MAX_INCREMENT, MAX_INCREMENT);
  L = map(L, -560, 560, -MAX_INCREMENT, MAX_INCREMENT);
  B = map(B, -560, 560, -MAX_INCREMENT, MAX_INCREMENT);
  R = map(R, -560, 560, -MAX_INCREMENT, MAX_INCREMENT);
  
  /*
  Serial.print("F Increment: ");
  Serial.print(F);
  Serial.print("     L Increment: ");
  Serial.print(L);
  Serial.print("     B Increment: ");
  Serial.print(B);
  Serial.print("     R Increment: ");
  Serial.print(R);
  Serial.print("\n");
  */
  
  //set new speeds
  this->frontSpd += F;
  this->leftSpd += L;
  this->backSpd += B;
  this->rightSpd += R;
  
  //  MOTOR_MIN < spd < MOTOR_MAX
  this->frontSpd = (this->frontSpd > MOTOR_MAX) ? MOTOR_MAX : ( (this->frontSpd < MOTOR_MIN) ? MOTOR_MIN : this->frontSpd );
  this->leftSpd = (this->leftSpd > MOTOR_MAX) ? MOTOR_MAX : ( (this->leftSpd < MOTOR_MIN) ? MOTOR_MIN : this->leftSpd );
  this->backSpd = (this->backSpd > MOTOR_MAX) ? MOTOR_MAX : ( (this->backSpd < MOTOR_MIN) ? MOTOR_MIN : this->backSpd );
  this->rightSpd = (this->rightSpd > MOTOR_MAX) ? MOTOR_MAX : ( (this->rightSpd < MOTOR_MIN) ? MOTOR_MIN : this->rightSpd );
  
  //write new speeds
  this->writeSpeeds();
}

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
