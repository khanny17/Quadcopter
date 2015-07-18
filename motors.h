#ifndef motors_h
#define motors_h

#include "Arduino.h"
#include "pry.h"
#include "Servo.h"

#define MOTOR_OFF 10
#define MOTOR_MIN 65
#define MOTOR_MAX 180

#define MIN_THROTTLE 65
#define MAX_THROTTLE 100          //160 so we can increment up to 180 with PRY displacement
#define THROTTLE_INCREMENT 10     //the max amount to increment the throttle by each time

#define OFFSET 20                 //the max offset between opposing motors for PRY
#define MAX_DEGREE_ERROR 90      //max degree range error for each motor pased on PRY

class MotorController
{
  public:
    MotorController();
    void init(int f, int l, int b, int r);
    void adjustSpeeds(PRY errors, int verticalVelocityError);
    void printSpeeds();
    void sendLow();
  private:
    void writeSpeeds(); 
    Servo front;
    Servo left;
    Servo back;
    Servo right;
    int frontSpd;
    int leftSpd;
    int rightSpd;
    int backSpd;
    int throttle;
};

#endif
