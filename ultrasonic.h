#ifndef ultrasonic_h
#define ultrasonic_h

class Ultrasonic
{
  public:
    Ultrasonic(int pin);
    int getHeight(); //returns height in cm
    void update();
  private:
    int pin;
    int height;
};


#endif
