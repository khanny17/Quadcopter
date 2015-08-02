#include "PID.h"

pid::pid(float k_p, float k_i, float k_d){
  this->k_p = k_p;
  this->k_i = k_i;
  this->k_d = k_d;
  this->desired = 0;
  this->e_prev = 0;
  this->t_prev = 0; //cant set it here reliably. maybe make this a pointer and set it to a variable we will fill in later with the time the system actually starts running?
  this->sum = 0;
}

int pid::compute(float actual){
  unsigned long t = millis();
  float e = this->desired-actual;
  double p = this->k_p*e;
  
  if(t_prev == 0){ //TODO i dont want to check this every time.
    t_prev = millis();
  }
  
  this->sum += e*((float)(t-this->t_prev)/1000);
  
  double i = this->k_i*(this->sum);
  double d = this->k_d * ((float)(1000)*(e - this->e_prev)/(t-t_prev));
  
  
  this->e_prev = e;
  this->t_prev = t;
  
  return (p+i+d)/2;
}

void pid::setDesired(int desired){
  //reset values
  this->desired = desired;
  //this->e_prev = 0;
  //this->t_prev = millis();
  //this->sum = 0;
}

void pid::setGains(float k_p, float k_i, float k_d){
  this->k_p = k_p;
  this->k_i = k_i;
  this->k_d = k_d;
}
