#ifndef Motors_h
#define Motors_h

#include <cstdint>
#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/property_tree/ptree.hpp>
#include "Servo.h"
#include "../Utils/UtilityFunctions.h"

class MotorController
{
    public:
        explicit MotorController(boost::shared_ptr<boost::property_tree::ptree> config);
        void adjustSpeeds(int pitchCorrection, int rollCorrection, int yawCorrection, int verticalVelocityError);
        void printSpeeds();
        void sendLow();
        void sendHigh();

    private:
        void writeSpeeds(); 
        boost::shared_ptr<boost::property_tree::ptree> m_config;
        boost::scoped_ptr<Servo> m_front, m_left, m_back, m_right;
        int m_frontSpd, m_leftSpd, m_rightSpd, m_backSpd, m_throttle;

        int MOTOR_MAX, MOTOR_MIN, THROTTLE_INCREMENT, MAX_THROTTLE, MIN_THROTTLE;
};

#endif
