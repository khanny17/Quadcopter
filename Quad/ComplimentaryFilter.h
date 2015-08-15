#ifndef ComplimentaryFilter_h
#define ComplimentaryFilter_h

#include "Filter.h"
#include "Arduino.h"

class ComplimentaryFilter : Filter
{
  public:
    ComplimentaryFilter(float K_gyro);
    float filter(float accReading, float gyroReading);
  private:
    float K_gyro;
    float K_acc;
};

#endif
