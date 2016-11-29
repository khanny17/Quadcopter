#include "AttitudeDeterminator.h"
#include "Motors.h"
#include "Controller.h"
#include "Logger.h"

#define FRONT_PIN 6 //TODO config this
#define LEFT_PIN  4
#define BACK_PIN  5
#define RIGHT_PIN 7

AttitudeDeterminator* attitude;
MotorController* motors;
Controller* ctrl;
Logger* logger;

float pitch, roll, yaw;
int pitchCorrection, rollCorrection, yawCorrection;

int setup();
void loop();

int main(int argc, char **argv) 
{

    if(setup()){
        return -1;
    }

    while(1)
    {
        loop();
    }
}

int setup()
{
    logger = new Logger();

    motors = new MotorController(FRONT_PIN, LEFT_PIN, BACK_PIN, RIGHT_PIN);
    attitude = new AttitudeDeterminator(.5);
    ctrl = new Controller;


    logger->log("Configuration Complete");
}

void loop()
{
    //Get current sensor readings
    attitude->getAttitude(&pitch, &roll, &yaw);
    logger->log("Reading: " << pitch);

    //Calculate corrections
    ctrl->calcPryCorrection(pitch, roll, yaw, &pitchCorrection, &rollCorrection, &yawCorrection);

    //Adjust motor speeds
    motors->adjustSpeeds(pitchCorrection, rollCorrection, yawCorrection, 0); //Update motor with correction
}
