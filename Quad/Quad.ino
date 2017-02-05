#include <Wire.h>
#include <Servo.h>
#include <NewPing.h>
#include "AttitudeDeterminator.h"
#include "Motors.h"
#include "Controller.h"

// --- Configurations ---

// --- Accelerometer ---
static const double ACC_SMOOTHING_FACTOR  = 0.5;
static const double ACC_ZERO_SAMPLE_COUNT = 10;

// --- Motors ---
static const int FRONT_PIN = 6;
static const int LEFT_PIN  = 4;
static const int BACK_PIN  = 5;
static const int RIGHT_PIN = 7;

// --- END Configurations ---

IMU *imu;
Accelerometer *accelerometer;
Gyroscope *gyroscope;
AttitudeDeterminator *attitude;
MotorController *motors;
Controller *ctrl;

double pitch, roll, yaw;
int pitchCorrection, rollCorrection, yawCorrection;

void setup() {
    Serial.begin(9600);
  
    while(!Serial.available()) {
        Serial.println("Send any key to begin configuration");
        delay(3000);
    }

    Serial.println("Constructing IMU");
    imu = new IMU();
    
    Serial.println("Constructing Accelerometer");
    accelerometer = new Accelerometer(imu, ACC_SMOOTHING_FACTOR);
    
    Serial.println("Constructing Gyroscope");
    gyroscope = new Gyroscope(imu);
  
    Serial.println("Zeroing Accelerometer");
    accelerometer->calc_zero(ACC_ZERO_SAMPLE_COUNT);
    
    motors = new MotorController(FRONT_PIN, LEFT_PIN, BACK_PIN, RIGHT_PIN);
    attitude = new AttitudeDeterminator(0.98, accelerometer, gyroscope);
    ctrl = new Controller;
    
  
    Serial.println("Configuration Complete");
}

char c = 'S';
void loop() {
    if(Serial.available()){
        c = (char)Serial.read();
    }
    if(c == 'G'){
        //Get current sensor readings
        attitude->getAttitude(&pitch, &roll, &yaw);
        
        Serial.print("Reading: "); Serial.print(pitch); Serial.print('\n');
        
        //Calculate corrections
        ctrl->calcPryCorrection(pitch, roll, yaw, &pitchCorrection, &rollCorrection, &yawCorrection);
        
        //Adjust motor speeds
        motors->adjustSpeeds(pitchCorrection, rollCorrection, yawCorrection, 0); //Update motor with correction
    } else {
        motors->sendLow();
    }
}
