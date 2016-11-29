#ifndef PID_h
#define PID_h

#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::posix_time;

class PID 
{
  public:
    PID(float k_p, float k_i, float k_d);
    int compute(float actual);
    void setDesired(int desired);
    void setGains(float k_p, float k_i, float k_d);
    void reset();
  private:
    float k_p, k_i, k_d;
    float e_prev;
    ptime t_prev;
    float sum;
    int desired;
};
    
    


#endif
