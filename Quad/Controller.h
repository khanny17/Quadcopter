#ifndef Controller_h
#define Controller_h

#include "PID.h"

class Controller
{
  public:
    void calcPryCorrection(double pitch, double roll, double yaw, int* pitchCorrection, int* rollCorrection, int* yawCorrection);
    void setDesiredPry(double pitch, double roll, double yaw);
    void reset();
};

#endif
