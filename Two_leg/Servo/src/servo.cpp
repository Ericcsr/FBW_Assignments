#include "servo.hpp"
#include <vector>

// You can attach servo 1-4;
// You can check current angle of servo;
// You can set an angle to rotate to execute command;
// You can set an angle to rotate as well as speed to configure servo's motion.


using namespace std;

extern TIM_HandleTypeDef htim2;
extern int error_code;

Servo::Servo(int init_angle,int id)
{
  __init_angle = init_angle;
  __angle = init_angle;
  __servo_id = id;
  switch(__servo_id)
  {
    case 1:
      __channel = TIM_CHANNEL_1; 
      break;
    case 2:
      __channel = TIM_CHANNEL_2;
      break;
    case 3:
      __channel = TIM_CHANNEL_3;
      break;
    case 4:
      __channel = TIM_CHANNEL_4;
      break;
    default : // Error handler
      error_code = 1;
      while(1);
  }
  
  rawExec();
}


int Servo::angle2signal(int angle)
{
  int signal = (angle /0.9); // Convert to int to generate approximate signal
  return signal;
}

void Servo::setAngle(int angle)
{
  __angle = angle;
}

int Servo::getAngle(void)
{
  return __angle;
}

void Servo::resetAngle(void)
{
  __angle = __init_angle;
}

void Servo::rawExec(void)
{
  int signal = angle2signal(__angle);
  __HAL_TIM_SET_COMPARE(&htim2,__channel,signal);
}

void Servo::speedAngle(int angle,int speed)
{
 int increment = 1+speed*2;
 static int tick = 0;
 static bool flag = 0;
 if(0 == flag)
 {
   tick = HAL_GetTick();
   flag = 1;
 }
 else
 {
   if(HAL_GetTick() - tick > 10)
   {
     flag = 0;
     if(getAngle() < angle)
     {
       setAngle(getAngle()+increment);
       rawExec();
     }
     else
     {
       setAngle(angle);
       rawExec();
     }
   }
 }
}
