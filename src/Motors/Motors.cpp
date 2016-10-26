#include "Motors.h"

MotorController::MotorController(int f, int l, int b, int r){
    front = new Servo(f);
    left = new Servo(f);
    back = new Servo(f);
    right = new Servo(f);
    sendLow(); //To initialize the motors, they need to receive a low signal
    sleep(10); //Wait ten seconds to make sure the motors read it
}

void MotorController::sendHigh(){
    front->writeMicroseconds(MOTOR_MAX);
    left->writeMicroseconds(MOTOR_MAX);
    back->writeMicroseconds(MOTOR_MAX);
    right->writeMicroseconds(MOTOR_MAX);
}

void MotorController::sendLow(){
    front->writeMicroseconds(MOTOR_OFF);
    left->writeMicroseconds(MOTOR_OFF);
    back->writeMicroseconds(MOTOR_OFF);
    right->writeMicroseconds(MOTOR_OFF);
}

int F, L, B, R, i, T; //temp variables
void MotorController::adjustSpeeds(int pitchCorrection, int rollCorrection, int yawCorrection, int heightError){
    //Get combined error for each motor
    F = (pitchCorrection+yawCorrection);
    L = (rollCorrection-yawCorrection);
    B = (-pitchCorrection+yawCorrection);
    R = (-rollCorrection-yawCorrection);

    //Calculate the base throttle based on error in desired speed
    T = map(heightError, -100, 100, -THROTTLE_INCREMENT, THROTTLE_INCREMENT);
    throttle = constrain(throttle+T, MIN_THROTTLE, MAX_THROTTLE);

    // Set new speeds
    frontSpd = throttle+F;
    leftSpd = throttle+L;
    backSpd = throttle+B;
    rightSpd = throttle+R;

    //write new speeds
    writeSpeeds();
}

/**
 *  Constrains speeds and writes them out
 */
void MotorController::writeSpeeds(){
    front->writeMicroseconds(constrain(frontSpd, MOTOR_MIN, MOTOR_MAX));
    //this->left.writeMicroseconds(constrain(this->leftSpd, MOTOR_MIN, MOTOR_MAX));
    back->writeMicroseconds(constrain(backSpd, MOTOR_MIN, MOTOR_MAX));
    //this->right.writeMicroseconds(constrain(this->rightSpd, MOTOR_MIN, MOTOR_MAX));
}

void MotorController::printSpeeds(){
    Serial.print("Front: ");
    Serial.print(frontSpd);
    Serial.print("     Left: ");
    Serial.print(leftSpd);
    Serial.print("     Back: ");
    Serial.print(backSpd);
    Serial.print("     Right: ");
    Serial.print(rightSpd);
    Serial.print("\n");
}
