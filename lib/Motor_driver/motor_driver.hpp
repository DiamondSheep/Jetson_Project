
#pragma once 

#include <JetsonGPIO.h>
#include <memory>

class motor_driver {
public:
   motor_driver();
    
   ~motor_driver();
  
   motor_driver(unsigned short EnablePinA, unsigned short IN1, unsigned short IN2, 
		          unsigned short EnablePinB, unsigned short IN3, unsigned short IN4);
   motor_driver(unsigned short IN1, unsigned short IN2, 
		          unsigned short IN3, unsigned short IN4);
   // motor_driver(std::shared_ptr<GPIO::PWM> drive[], int IN1, int IN2, int IN3, int IN4, bool setup);
   
   void setSpeed(const unsigned short Val);
   const unsigned short getSpeed();
   void forward();
   void backward();
   
   void run();
   void stop();

private:
   unsigned short EN[2];
   unsigned short left[2];
   unsigned short right[2];

   unsigned short pwmVal;

   std::shared_ptr<GPIO::PWM> Drive_PWM_left, Drive_PWM_right;

   bool setup; //controls whether or not we control the PWM object.  False if we don't.
};
