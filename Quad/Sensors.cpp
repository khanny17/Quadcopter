#include "Sensors.h"

imu imu;
Ultrasonic ultrasonic; //TODO config the pins?

SensorInterface::SensorInterface(float K_gP){
  this->K_gyro_pitch = K_gP;
  this->K_acc_pitch = 1-K_gP;
}

/**
 * Performs any initialization necessary for the Sensors
 * NOTE: The initialization for some sensors, such as the imu,
 *         will not work if this is placed in the constructor,
 *         which is why this function exists.
 */
void SensorInterface::init(){
  imu.init();
  this->pitch = imu.getAccData(Y);
  this->pitch_t_prev = millis(); //maybe take the current time?

  //Buffer up Pitch readings to clear any starting noise
  int i;
  for(i = 0; i < 50; ++i){
    this->getPitch();
  }
}

/**
 *  Updates sensor readings and returns the current PRY
 */
PRY SensorInterface::getPRY(){
  imu.update();
  //ultrasonic.update();
  return (PRY){ this->getPitch(), 0, 0 };
}

/**
 * Determines the current pitch of the quad using gyroscope and accelerometer
 */
float SensorInterface::getPitch(){
  unsigned long t = millis();
  
  Serial.println(imu.getGyroData(Y));
  
  float d_gyro = imu.getGyroData(Y) * ((float)(t-this->pitch_t_prev)/1000); // get the change in degrees for the past cycle
  Serial.println(d_gyro);
  float gyro = d_gyro + this->pitch; //calc gyro value   s*delta_t+s_prev
  
  Serial.println(gyro);
  Serial.println();
  
  float acc = imu.getAccData(Y); //calc accelerometer value
  
  this->pitch_t_prev = t; //save new time
  this->pitch = this->K_gyro_pitch * gyro + this->K_acc_pitch * acc; //save new pitch
  
  //Serial.println(this->pitch);
  return this->pitch;
}

/**
 * Determines the current roll of the quad using gyroscope and accelerometer
 */
float SensorInterface::getRoll(){
  unsigned long t = millis();
  
  float d_gyro = imu.getGyroData(X) * ((float)(t-this->pitch_t_prev)/1000); // get the change in degrees for the past cycle
  float gyro = d_gyro + this->pitch; //calc gyro value   s*delta_t+s_prev
  
  //Serial.println(gyro);
  
  float acc = imu.getAccData(X); //calc accelerometer value
  
  this->pitch_t_prev = t; //save new time
  this->pitch = this->K_gyro_pitch * gyro + this->K_acc_pitch * acc; //save new pitch
  
  //Serial.println(this->pitch);
  return this->pitch;
}

int SensorInterface::getHeight(){
  //eventually this function will decide to use the ultrasonic or the barometer based on the altitude
  return ultrasonic.getHeight();
}

/**
 * Returns the vertical velocity of the quad in centimeters per second
 */
int velocity, prevHeight = 0;
unsigned long curTime, prevTime;
int SensorInterface::getVerticalVelocity(){
  curTime = millis();
  velocity = (1000 * (this->getHeight() - prevHeight)) / (curTime - prevTime); //1000 * cm/ms)
  prevHeight = this->getHeight();
  prevTime = curTime;
  return velocity;
}

void SensorInterface::testImu(){ 
  imu.update();
  imu.prettyPrint();
}


