#include "Motors.h"

using namespace boost;
using namespace boost::property_tree;

MotorController::MotorController(shared_ptr<ptree> config){
    front.reset(new Servo(config->get<int>("Motors.FrontPin")));
    left.reset(new Servo(config->get<int>("Motors.LeftPin")));
    back.reset(new Servo(config->get<int>("Motors.BackPin")));
    right.reset(new Servo(config->get<int>("Motors.RightPin")));

    throttle = 0;
    frontSpd = 0;
    leftSpd = 0;
    backSpd = 0;
    rightSpd = 0;

    sendLow(); //To initialize the motors, they need to receive a low signal
    this_thread::sleep_for(chrono::seconds(10)); //Wait ten seconds to make sure the motors read it
}

void MotorController::sendHigh(){
    front->writeMicroseconds(MOTOR_MAX);
    left->writeMicroseconds(MOTOR_MAX);
    back->writeMicroseconds(MOTOR_MAX);
    right->writeMicroseconds(MOTOR_MAX);
}

void MotorController::sendLow(){
    front->writeMicroseconds(MOTOR_OFF);
    left->writeMicroseconds(MOTOR_OFF);
    back->writeMicroseconds(MOTOR_OFF);
    right->writeMicroseconds(MOTOR_OFF);
}

int F, L, B, R, i, T; //temp variables
void MotorController::adjustSpeeds(int pitchCorrection, int rollCorrection, int yawCorrection, int heightError){
    //Get combined error for each motor
    F = (pitchCorrection+yawCorrection);
    L = (rollCorrection-yawCorrection);
    B = (-pitchCorrection+yawCorrection);
    R = (-rollCorrection-yawCorrection);

    //Calculate the base throttle based on error in desired speed
    T = UtilityFunctions::map(heightError, -100, 100, -THROTTLE_INCREMENT, THROTTLE_INCREMENT);
    throttle = UtilityFunctions::constrain(throttle+T, MIN_THROTTLE, MAX_THROTTLE);

    // Set new speeds
    frontSpd = UtilityFunctions::constrain(throttle+F, MOTOR_MIN, MOTOR_MAX);
    leftSpd = UtilityFunctions::constrain(throttle+L, MOTOR_MIN, MOTOR_MAX);
    backSpd = UtilityFunctions::constrain(throttle+B, MOTOR_MIN, MOTOR_MAX);
    rightSpd = UtilityFunctions::constrain(throttle+R, MOTOR_MIN, MOTOR_MAX);

    //write new speeds
    writeSpeeds();
}

/**
 *  Constrains speeds and writes them out
 */
void MotorController::writeSpeeds(){
    front->writeMicroseconds(frontSpd);
    //this->left.writeMicroseconds(leftSpd);
    back->writeMicroseconds(backSpd);
    //this->right.writeMicroseconds(rightSpd);
}

void MotorController::printSpeeds(){
    //TODO log this maybe? dont use cout outside of our wrapped logging library
    std::cout << "Front: " << frontSpd << std::endl;
    std::cout << "Left: "  << leftSpd << std::endl;
    std::cout << "Back: "  << backSpd << std::endl;
    std::cout << "Right: " << rightSpd << std::endl;
}
