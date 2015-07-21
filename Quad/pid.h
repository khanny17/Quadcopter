#ifndef pid_h
#define pid_h

#include "Arduino.h"

class pid
{
  public:
    pid(float k_p, float k_i, float k_d);
    int compute(int actual);
    void setDesired(int desired);
  private:
    float k_p, k_i, k_d;
    int e_prev;
    int t_prev;
    float sum;
    int desired;
};
    
    


#endif
