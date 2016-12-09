#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/scoped_ptr.hpp>
#include "AttitudeDeterminator.h"
#include "Motors.h"
#include "Controller.h"

using namespace boost;
using namespace boost::property_tree;

scoped_ptr<AttitudeDeterminator> attitudeDeterminator;
scoped_ptr<MotorController> motors;
scoped_ptr<Controller> ctrl;

int pitchCorrection, rollCorrection, yawCorrection;

void setup(shared_ptr<ptree> config);
void loop();

int main(int argc, char **argv) 
{
    BOOST_LOG_TRIVIAL(info) << "Hello!";

    //Read Config
    shared_ptr<ptree> config(new ptree);
    ini_parser::read_ini("config.cfg", *config.get());

    BOOST_LOG_TRIVIAL(info) << "Config import Success";
    
    try {
        setup(config);
    }
    catch(std::string e) {
        BOOST_LOG_TRIVIAL(fatal) << e;
        exit(1);
    }
    

    while(1)
    {
        loop();
    }
}

void setup(shared_ptr<ptree> config)
{
    attitudeDeterminator.reset(new AttitudeDeterminator(config));
    ctrl.reset(new Controller);
    motors.reset(new MotorController(config));

    BOOST_LOG_TRIVIAL(info) << "Setup Complete";
}

void loop()
{
    //Get current sensor readings
    auto attitude = attitudeDeterminator->getAttitude();
    BOOST_LOG_TRIVIAL(info) << "Pitch: " << attitude.pitch;

    //Calculate corrections
    //ctrl->calcPryCorrection(pitch, roll, yaw, &pitchCorrection, &rollCorrection, &yawCorrection);

    //Adjust motor speeds
    //motors->adjustSpeeds(pitchCorrection, rollCorrection, yawCorrection, 0); //Update motor with correction
}

