#include "main.h"
#include <vector>

using namespace std;

class Servo
{
  private:
    int __init_angle;
    int __angle;
    int __servo_id;
    uint32_t __channel;
    int angle2signal(int angle);
  public:
    Servo(int init_angle,int id);
    void setAngle(int angle);
    int getAngle(void);
    void resetAngle(void);
    void rawExec(void);
    void speedAngle(int angle,int speed);
};
