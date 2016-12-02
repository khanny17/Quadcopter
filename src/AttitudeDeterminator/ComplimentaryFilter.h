#ifndef ComplimentaryFilter_h
#define ComplimentaryFilter_h

#include <boost/log/trivial.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/circular_buffer.hpp>
#include "Filter.h"

#define ACC_BUFFER_SIZE 2
#define GYRO_BUFFER_SIZE 2

class ComplimentaryFilter : public Filter
{
    public:
        explicit ComplimentaryFilter(float K_gyro);
        float filter(float accReading, float gyroReading);
    private:
        float K_gyro;
        float K_acc;
        float pitch;
        boost::scoped_ptr<boost::posix_time::ptime> curTime, prevTime;
        boost::scoped_ptr<boost::circular_buffer<float>> accBuffer;
        boost::scoped_ptr<boost::circular_buffer<float>> gyroBuffer;
        void bufferValues(float accReading, float gyroReading, float* acc, float* gyro);
        float calcAverage(boost::circular_buffer<float> buffer);
};


#endif
