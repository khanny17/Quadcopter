#ifndef ComplimentaryFilter_h
#define ComplimentaryFilter_h

#include <boost/log/trivial.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/scoped_ptr.hpp>
#include "Filter.h"
#include "Buffer.h"


#define ACC_BUFFER_SIZE 2
#define GYRO_BUFFER_SIZE 2

class ComplimentaryFilter : public Filter
{
  public:
    ComplimentaryFilter(float K_gyro);
    float filter(float accReading, float gyroReading);
  private:
    float K_gyro;
    float K_acc;
    float pitch;
    boost::scoped_ptr<ptime> curTime, prevTime;
    Buffer<float> accBuffer{ACC_BUFFER_SIZE};
    Buffer<float> gyroBuffer{GYRO_BUFFER_SIZE};
    void bufferValues(float accReading, float gyroReading, float* acc, float* gyro);
};

#endif
