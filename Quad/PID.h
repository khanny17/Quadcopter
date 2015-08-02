#ifndef PID_h
#define PID_h

#include "Arduino.h"

class pid
{
  public:
    pid(float k_p, float k_i, float k_d);
    int compute(float actual);
    void setDesired(int desired);
    void setGains(float k_p, float k_i, float k_d);
  private:
    float k_p, k_i, k_d;
    float e_prev;
    unsigned long t_prev;
    float sum;
    int desired;
};
    
    


#endif
