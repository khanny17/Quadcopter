#include "controller.h"
#include "pid.h"
#include "pry.h"


pid pitchPID(3, .1, .8);  //it is balancing with 3, .1, .8
pid rollPID(1, .1, .5); //TODO config this
pid yawPID(1, 1, 1);
pid vertVelocityPID(1, .5, .5);

PRY Controller::calcPryCorrection(PRY actual){
  /*int presult = 
    pitchPID.compute(actual.pitch);
    Serial.println(presult);*/
  return (PRY){
    pitchPID.compute(actual.pitch),
    0,//rollPID.compute(actual.roll),
    0 //TODO implement yaw!
  };
}

/**
 * Calculates error in the vertical speed
 *  - This function updates what speed we want to be going based on how close to actual height we are.
 *     Once we are within 1m of the desired height, we start to decrease our speed.
 *     Our max speed is one half the error in height, ie if we are at 1m, the speed is .5m/s,
 *      if at .5m height, speed is .25m/s
 *    ie: dy/dt = .5y -> y = ce^(t/2) -> we get exponentially slower as we approach our desired height, which is good!
 *  NOTE: unit for velocity is cm/s
 */
int Controller::calcVerticalVelocityError(int actualVelocity, int heightError){
  heightError = constrain(heightError, -100, 100);  //Constrain to 1m
  vertVelocityPID.setDesired(heightError/2); //Will set velocity to be half as fast as the error in height.
  return vertVelocityPID.compute(actualVelocity);
}

int Controller::calcHeightError(int actual){
  return this->desiredHeight - actual;
}

/**
 * Sets the desired orientation of the quad through
 *  the pitch roll and yaw values in degrees
 */
void Controller::setDesiredPry(PRY* desired){
  pitchPID.setDesired(desired->pitch);
  rollPID.setDesired(desired->roll);
  yawPID.setDesired(desired->yaw);
}

/**
 * Sets the desired height of the quadcopter
 * @param desired - the height in centimeters
 */
void Controller::setDesiredHeight(int desired){
  this->desiredHeight = desired;
}

void Controller::setPitchPIDGains(float P, float I, float D){
  pitchPID.setGains(P, I, D);
}

