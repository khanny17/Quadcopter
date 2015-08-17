#include <Wire.h>
#include "AttitudeDeterminator.h"

AttitudeDeterminator* attitude;
float pitch, roll, yaw;


void setup() {
  Serial.begin(9600);
  delay(2000);
  attitude = new AttitudeDeterminator;
}


void loop() {
  attitude->getAttitude(&pitch, &roll, &yaw);
  Serial.print("Reading: "); Serial.print(pitch); Serial.print('\n');
}

