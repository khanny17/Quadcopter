#ifndef ComplimentaryFilter_h
#define ComplimentaryFilter_h

#include "Filter.h"
#include "Arduino.h"
#include "Buffer.h"

#define ACC_BUFFER_SIZE 2
#define GYRO_BUFFER_SIZE 2

class ComplimentaryFilter : public Filter
{
  public:
    ComplimentaryFilter(double K_gyro);
    double filter(double accReading, double gyroReading);
  private:
    double K_gyro;
    double K_acc;
    double angle;
    unsigned long prevTime;
};

#endif
