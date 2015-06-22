#ifndef motors_h
#define motors_h

#include "Arduino.h"
#include "pryh.h"
#include "Servo.h"

#define MOTOR_OFF 10
#define MOTOR_MIN 65
#define MOTOR_MAX 180

#define MAX_INCREMENT 20

class MotorController
{
  public:
    MotorController(int f, int l, int b, int r);
    void adjustSpeeds(PRYH errors);
  private:
    void writeSpeeds(); 
    Servo front;
    Servo left;
    Servo back;
    Servo right;
    int* speeds; //f, l, b, r
};

#endif
