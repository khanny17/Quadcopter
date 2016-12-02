#ifndef Servo_h
#define Servo_h

class Servo
{
    public:
        explicit Servo(int pin);
        void writeMicroseconds(int micros);

    private:
        int pin;
};

#endif
