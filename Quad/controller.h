#ifndef controller_h
#define controller_h

#include "pry.h"

class Controller
{
  public:
    PRY calcPryCorrection(PRY actual);
    int calcVerticalVelocityError(int actual, int heightError);
    int calcHeightError(int actual);
    void setDesiredPry(PRY* desired);
    void setDesiredHeight(int desired);
  private:
    int desiredHeight;
};

#endif
