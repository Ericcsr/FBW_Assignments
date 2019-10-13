#include "main.h"
#include "servo.hpp"
using namespace std;

void user_setup(void)
{
  
}


void user_loop(void)
{
  Servo myservo(10,1);
  // Testing Program; Run the rotate the motor and rotate it back.
  while(1)
  {
    myservo.setAngle(100);
    myservo.rawExec();
    HAL_Delay(1000);
    myservo.setAngle(10);
    myservo.rawExec();
    HAL_Delay(1000);
    HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_14); // LED Breath Light Indicate the code is still runing.
  }
}
