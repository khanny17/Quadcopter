#include "PID.h"

PID::PID(float proportion, float integration, float derivative){
    k_p = proportion;
    k_i = integration;
    k_d = derivative;
    desired = 0;
    e_prev = 0;
    t.reset();
    t_prev.reset();
    sum = 0;
}

int PID::compute(float actual){
    t.reset(new ptime(microsec_clock::local_time()));
    float e = desired-actual;
    double p = k_p*e;

    if(t_prev.get() == 0){ //TODO i dont want to check this every time.
        t_prev.reset(new ptime(microsec_clock::local_time()));
    }

    time_duration diff = *t - *t_prev;
    unsigned long delta_t = diff.total_milliseconds();


    sum += e*((float)(delta_t)/1000);

    double i = k_i*(sum);
    double d = k_d * ((float)(1000)*(e - e_prev)/(delta_t));


    e_prev = e;
    t_prev.swap(t);

    return (p+i+d)/2;
}

void PID::setDesired(int newDesired){
    //reset values
    desired = newDesired;
    //this->e_prev = 0;
    //this->t_prev = millis();
    //this->sum = 0;
}

void PID::setGains(float k_p, float k_i, float k_d){
    this->k_p = k_p;
    this->k_i = k_i;
    this->k_d = k_d;
}

void PID::reset(){
    e_prev = 0;
    t_prev.reset();
    sum = 0;
}
