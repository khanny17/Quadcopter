#ifndef ultrasonic_h
#define ultrasonic_h

#include "Arduino.h"
#include "Buffer.h"
#include "NewPing.h"

#define TRIGGER_PIN 8
#define ECHO_PIN 9
#define MAX_DISTANCE 450 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.




class Ultrasonic
{
  public:
    int getHeight(); //returns height in cm
    void update();
  private:
    int height;
};


#endif
