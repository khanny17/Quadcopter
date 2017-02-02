/**
 * Abstract class for filters to combine sensor readings
 */
#ifndef Filter_h
#define Filter_h

class Filter
{
  public:
    virtual double filter(double accReading, double gyroReading) = 0;
};

#endif
