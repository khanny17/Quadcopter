#include "Ultrasonic.h"

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int Ultrasonic::getHeight(){
  return this->height;
}

long duration;
void Ultrasonic::update(){
  unsigned int duration = sonar.ping(); // Send ping, get ping time in microseconds (uS).

  // convert the time into a distance in cm
  this->height = duration / US_ROUNDTRIP_CM;
}
