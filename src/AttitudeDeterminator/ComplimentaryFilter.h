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
        explicit ComplimentaryFilter(double K_gyro);
        double filter(double accReading, double gyroReading) override;
    private:
        double K_gyro;
        double K_acc;
        double pitch;
        boost::scoped_ptr<boost::posix_time::ptime> curTime, prevTime;
        boost::scoped_ptr<boost::circular_buffer<double>> accBuffer;
        boost::scoped_ptr<boost::circular_buffer<double>> gyroBuffer;
        void bufferValues(double accReading, double gyroReading, double* acc, double* gyro);
        double calcAverage(boost::circular_buffer<double> buffer);
};


#endif
