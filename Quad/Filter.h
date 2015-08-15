/**
 * Abstract class for filters to combine sensor readings
 */
#ifndef Filter_h
#define Filter_h

class Filter
{
  public:
    virtual float filter(float accReading, float gyroReading) = 0;
};

#endif
