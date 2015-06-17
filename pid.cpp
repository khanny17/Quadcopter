#include "Arduino.h"
#include "pid.h"

pid::pid(){
  this->desired = 0;
  this->e_prev = 0;
  this->t_prev = millis();
  this->sum = 0;
}

int pid::compute(int actual){
  int t = millis();
  int e = this->desired-actual;
  double p = k_p*e;
  double i = k_i*(this->sum+(e/(t-this->t_prev)));
  double d = k_d*(e - this->e_prev)/(t-t_prev);
  
  return p+i+d;
}

void pid::setDesired(int desired){
  //reset values
  this->desired = desired;
  this->e_prev = 0;
  this->t_prev = millis();
  this->sum = 0;
}
