#include "Controller.h"

PID pitchPID(3, 0, .8);  //it is balancing with 3, .1, .8
PID rollPID(1, .1, .5); //TODO config this
PID yawPID(1, 1, 1);
PID vertVelocityPID(1, .5, .5);

void Controller::calcPryCorrection(float pitch, float roll, float yaw,
                                   int* pitchCorrection, int* rollCorrection, int* yawCorrection){
    *pitchCorrection = pitchPID.compute(pitch);
    *rollCorrection = 0;
    *yawCorrection = 0;
}

/**
 * Sets the desired orientation of the quad through
 *  the pitch roll and yaw values in degrees
 */
void Controller::setDesiredPry(float pitch, float roll, float yaw){
  pitchPID.setDesired(pitch);
  rollPID.setDesired(roll);
  yawPID.setDesired(yaw);
}

void Controller::reset(){
  pitchPID.reset();
  rollPID.reset();
}

