#ifndef Controller_h
#define Controller_h

#include "PID.h"
#include "PRY.h"

class Controller
{
  public:
    PRY calcPryCorrection(PRY actual);
    int calcVerticalVelocityError(int actual, int heightError);
    int calcHeightError(int actual);
    void setDesiredPry(PRY* desired);
    void setDesiredHeight(int desired);
    void setPitchPIDGains(float p, float i, float d);
    void reset();
  private:
    int desiredHeight;
};

#endif
