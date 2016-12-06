#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "AttitudeDeterminator.h"
#include "Motors.h"
#include "Controller.h"

using namespace boost;
using namespace boost::property_tree;

AttitudeDeterminator* attitude;
MotorController* motors;
Controller* ctrl;

float pitch, roll, yaw;
int pitchCorrection, rollCorrection, yawCorrection;

int setup(shared_ptr<ptree> config);
void loop();

int main(int argc, char **argv) 
{
    BOOST_LOG_TRIVIAL(info) << "Hello!";

    //Read Config
    shared_ptr<ptree> config(new ptree);
    ini_parser::read_ini("config.cfg", *config.get());

    BOOST_LOG_TRIVIAL(info) << "Config import Success";
    
    if(setup(config)){
        return -1;
    }

    while(1)
    {
        loop();
    }
}

int setup(shared_ptr<ptree> config)
{
    motors = new MotorController(config);
    attitude = new AttitudeDeterminator(config);
    ctrl = new Controller;


    BOOST_LOG_TRIVIAL(info) << "Setup Complete";

    return 0;
}

void loop()
{
    //Get current sensor readings
    attitude->getAttitude(&pitch, &roll, &yaw);
    BOOST_LOG_TRIVIAL(info) << "Reading: " << pitch;

    //Calculate corrections
    ctrl->calcPryCorrection(pitch, roll, yaw, &pitchCorrection, &rollCorrection, &yawCorrection);

    //Adjust motor speeds
    motors->adjustSpeeds(pitchCorrection, rollCorrection, yawCorrection, 0); //Update motor with correction
}
