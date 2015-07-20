#include "Arduino.h"
#include "pid.h"

pid::pid(float k_p, float k_i, float k_d){
  this->k_p = k_p;
  this->k_i = k_i;
  this->k_d = k_d;
  this->desired = 0;
  this->e_prev = 0;
  this->t_prev = millis();
  this->sum = 0;
}

int pid::compute(int actual){
  int t = millis();
  int e = this->desired-actual;
  double p = this->k_p*e;
  double i = this->k_i*(this->sum+(e/(t-this->t_prev)));
  double d = this->k_d*(e - this->e_prev)/(t-t_prev);
  
  this->sum += e; //add to our sum
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
