#include "Motors.h"

using namespace boost;
using namespace boost::property_tree;

MotorController::MotorController(shared_ptr<ptree> config) : m_config(config) {
    //Load Constants from config
    MOTOR_MAX = m_config->get<int>("Motors.MotorMax");
    MOTOR_MIN = m_config->get<int>("Motors.MotorMin");
    THROTTLE_INCREMENT = m_config->get<int>("Motors.ThrottleIncrement");
    MIN_THROTTLE = m_config->get<int>("Motors.MinThrottle");
    MAX_THROTTLE = m_config->get<int>("Motors.MaxThrottle");


    //Setup servos
    m_front.reset(new Servo(config->get<int>("Motors.FrontPin")));
    m_left.reset(new Servo(config->get<int>("Motors.LeftPin")));
    m_back.reset(new Servo(config->get<int>("Motors.BackPin")));
    m_right.reset(new Servo(config->get<int>("Motors.RightPin")));

    m_throttle = 0;
    m_frontSpd = 0;
    m_leftSpd = 0;
    m_backSpd = 0;
    m_rightSpd = 0;

    sendLow(); //To initialize the motors, they need to receive a low signal
    this_thread::sleep_for(chrono::seconds(10)); //Wait ten seconds to make sure the motors read it
}

void MotorController::sendHigh(){
    m_front->writeMicroseconds(MOTOR_MAX);
    m_left->writeMicroseconds(MOTOR_MAX);
    m_back->writeMicroseconds(MOTOR_MAX);
    m_right->writeMicroseconds(MOTOR_MAX);
}

void MotorController::sendLow(){
    m_front->writeMicroseconds(MOTOR_MIN);
    m_left->writeMicroseconds(MOTOR_MIN);
    m_back->writeMicroseconds(MOTOR_MIN);
    m_right->writeMicroseconds(MOTOR_MIN);
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
    m_throttle = UtilityFunctions::constrain(m_throttle+T, MIN_THROTTLE, MAX_THROTTLE);

    // Set new speeds
    m_frontSpd = UtilityFunctions::constrain(m_throttle+F, MOTOR_MIN, MOTOR_MAX);
    m_leftSpd = UtilityFunctions::constrain(m_throttle+L, MOTOR_MIN, MOTOR_MAX);
    m_backSpd = UtilityFunctions::constrain(m_throttle+B, MOTOR_MIN, MOTOR_MAX);
    m_rightSpd = UtilityFunctions::constrain(m_throttle+R, MOTOR_MIN, MOTOR_MAX);

    //write new speeds
    writeSpeeds();
}

/**
 *  Constrains speeds and writes them out
 */
void MotorController::writeSpeeds(){
    m_front->writeMicroseconds(m_frontSpd);
    //this->left.writeMicroseconds(leftSpd);
    m_back->writeMicroseconds(m_backSpd);
    //this->right.writeMicroseconds(rightSpd);
}

void MotorController::printSpeeds(){
    //TODO log this maybe? dont use cout outside of our wrapped logging library
    std::cout << "Front: " << m_frontSpd << std::endl;
    std::cout << "Left: "  << m_leftSpd << std::endl;
    std::cout << "Back: "  << m_backSpd << std::endl;
    std::cout << "Right: " << m_rightSpd << std::endl;
}
