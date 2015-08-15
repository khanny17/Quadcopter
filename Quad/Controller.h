#ifndef Controller_h
#define Controller_h

#include "PID.h"

class Controller
{
  public:
    void calcPryCorrection();
    int calcVerticalVelocityError(int actual, int heightError);
    int calcHeightError(int actual);
    void setDesiredPry();
    void setDesiredHeight(int desired);
    void setPitchPIDGains(float p, float i, float d);
    void reset();
  private:
    int desiredHeight;
};

#endif
