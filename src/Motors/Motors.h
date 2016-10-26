#ifndef Motors_h
#define Motors_h

#include "Servo.h"

#define MOTOR_OFF   700   //Min possible signal
#define MOTOR_MIN   800   //Min allowed motor value
#define MOTOR_MAX  1900   //Max allowed motor value
#define MOTOR_FULL 2000   //Max possible signal

#define MIN_THROTTLE 1000
#define MAX_THROTTLE 1001          //160 so we can increment up to 180 with PRY displacement
#define THROTTLE_INCREMENT 10     //the max amount to increment the throttle by each time

class MotorController
{
    public:
        MotorController(int f, int l, int b, int r);
        void adjustSpeeds(int pitchCorrection, int rollCorrection, int yawCorrection, int verticalVelocityError);
        void printSpeeds();
        void sendLow();
        void sendHigh();

    private:
        void writeSpeeds(); 
        Servo *front, *left, *back, *right;
        int frontSpd, leftSpd, rightSpd, backSpd, throttle;
};

#endif
