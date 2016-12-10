#include "ComplimentaryFilter.h"

using namespace boost;
using namespace boost::posix_time;

ComplimentaryFilter::ComplimentaryFilter(double t_K_gyro){
    if(K_gyro > 1 || K_gyro < 0){
        BOOST_LOG_TRIVIAL(info) << "WARNING: invalid value for K_gyro";
    }
    K_gyro = t_K_gyro;
    K_acc = 1-K_gyro;
    prevTime.reset();
    curTime.reset();
    pitch = 0;

    accBuffer.reset(new circular_buffer<double>(ACC_BUFFER_SIZE));
    accBuffer.reset(new circular_buffer<double>(GYRO_BUFFER_SIZE));
}

double ComplimentaryFilter::filter(double accReading, double gyroReading){
    double gyro, acc;
    bufferValues(accReading, gyroReading, &acc, &gyro);

    if(prevTime.get() == 0){ //TODO i dont want to check this every time.
        prevTime.reset(new ptime(microsec_clock::local_time()));
    }
    curTime.reset(new ptime(microsec_clock::local_time()));

    //Integrate gyro reading:
    time_duration diff = *curTime - *prevTime;
    auto delta_t = diff.total_milliseconds();
    double dt = static_cast<double>(delta_t)/1000;
    double G = gyro*dt + pitch;

    prevTime.swap(curTime); //save time for next cycle
    pitch = K_gyro * G + K_acc * acc; //save pitch

    return pitch;
}

void ComplimentaryFilter::bufferValues(double accReading, double gyroReading, double* acc, double* gyro){
    accBuffer.get()->push_back(accReading);
    gyroBuffer.get()->push_back(gyroReading);
    *acc = calcAverage(*accBuffer.get());
    *gyro = calcAverage(*gyroBuffer.get());
}

double ComplimentaryFilter::calcAverage(circular_buffer<double> buffer) {
    double total = 0;
    for(int i = buffer.size() - 1; i >= 0; --i) {
        total += buffer[i];
    }
    return total;
}
