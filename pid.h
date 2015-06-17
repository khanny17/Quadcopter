#ifndef pid_h
#define pid_h

#include "Arduino.h"

#define k_p 1
#define k_i 0.1
#define k_d 1

class pid
{
  public:
    pid();
    int compute(int actual);
    void setDesired(int desired);
  private:
    int e_prev;
    int t_prev;
    int sum;
    int desired;
};
    
    


#endif
