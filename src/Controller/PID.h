#ifndef PID_h
#define PID_h

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/scoped_ptr.hpp>

using namespace boost;
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
    scoped_ptr<ptime> t, t_prev;
    float sum;
    int desired;
};
    
    


#endif
