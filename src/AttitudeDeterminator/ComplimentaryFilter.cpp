#include "ComplimentaryFilter.h"

using namespace boost;
using namespace boost::posix_time;

ComplimentaryFilter::ComplimentaryFilter(float t_K_gyro){
    if(K_gyro > 1 || K_gyro < 0){
        BOOST_LOG_TRIVIAL(info) << "WARNING: invalid value for K_gyro";
    }
    K_gyro = t_K_gyro;
    K_acc = 1-K_gyro;
    prevTime.reset();
    curTime.reset();
    pitch = 0;

    accBuffer.reset(new circular_buffer<float>(ACC_BUFFER_SIZE));
    accBuffer.reset(new circular_buffer<float>(GYRO_BUFFER_SIZE));
}

float ComplimentaryFilter::filter(float accReading, float gyroReading){
    float gyro, acc;
    bufferValues(accReading, gyroReading, &acc, &gyro);

    if(prevTime.get() == 0){ //TODO i dont want to check this every time.
        prevTime.reset(new ptime(microsec_clock::local_time()));
    }
    curTime.reset(new ptime(microsec_clock::local_time()));

    //Integrate gyro reading:
    time_duration diff = *curTime - *prevTime;
    unsigned long delta_t = diff.total_milliseconds();
    float dt = static_cast<float>(delta_t)/1000;
    float G = gyro*dt + pitch;

    prevTime.swap(curTime); //save time for next cycle
    pitch = K_gyro * G + K_acc * acc; //save pitch

    return pitch;
}

void ComplimentaryFilter::bufferValues(float accReading, float gyroReading, float* acc, float* gyro){
    accBuffer.get()->push_back(accReading);
    gyroBuffer.get()->push_back(gyroReading);
    *acc = calcAverage(*accBuffer.get());
    *gyro = calcAverage(*gyroBuffer.get());
}

float ComplimentaryFilter::calcAverage(circular_buffer<float> buffer) {
    float total = 0;
    for(int i = buffer.size() - 1; i >= 0; --i) {
        total += buffer[i];
    }
    return total;
}
