#ifndef Controller_h
#define Controller_h

#include "PID.h"

class Controller
{
  public:
    void calcPryCorrection(float pitch, float roll, float yaw, int* pitchCorrection, int* rollCorrection, int* yawCorrection);
    void setDesiredPry(float pitch, float roll, float yaw);
    void reset();
};

#endif
