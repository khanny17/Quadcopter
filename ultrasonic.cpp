#include "Arduino.h"
#include "ultrasonic.h"

Ultrasonic::Ultrasonic(int pin){
  this->pin = pin;
}

long duration;
int Ultrasonic::getHeight(){
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(this->pin, OUTPUT);
  digitalWrite(this->pin, LOW);
  delayMicroseconds(2);
  digitalWrite(this->pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(this->pin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(this->pin, INPUT);
  duration = pulseIn(this->pin, HIGH);

  // convert the time into a distance in cm
  return duration / 58;
}
