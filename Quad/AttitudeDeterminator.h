/**
 * Determines attitude of the quadcopter using sensors and filters
 */
#ifndef AttitudeDeterminator_h
#define AttitudeDeterminator_h

#include "Arduino.h"

class AttitudeDeterminator
{
  public:
    void getPRY(float* pitch, float* roll, float* yaw);
    void init();
};


#endif
