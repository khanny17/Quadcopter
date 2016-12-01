#include "ComplimentaryFilter.h"

ComplimentaryFilter::ComplimentaryFilter(float K_gyro){
    if(K_gyro > 1 || K_gyro < 0){
        BOOST_LOG_TRIVIAL(info) << "WARNING: invalid value for K_gyro";
    }
    this->K_gyro = K_gyro;
    this->K_acc = 1-K_gyro;
    prevTime.reset();
    curTime.reset();
    pitch = 0;
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
    float dt = (float)(delta_t)/1000;
    float G = gyro*dt + pitch;

    prevTime.swap(curTime); //save time for next cycle
    pitch = K_gyro * G + K_acc * acc; //save pitch

    return pitch;
}

void ComplimentaryFilter::bufferValues(float accReading, float gyroReading, float* acc, float* gyro){
    accBuffer.add(accReading);
    gyroBuffer.add(gyroReading);
    *acc = accBuffer.average();
    *gyro = gyroBuffer.average();
}
