
#pragma once 

#include <JetsonGPIO.h>
#include <memory>

class L298N_Jetson {
public:
   // 构造函数（初始化对象）和析构函数
   L298N_Jetson();
    
   ~L298N_Jetson();
  
   // main函数里用的是这个 ↓
   L298N_Jetson(unsigned short EnablePinA, unsigned short IN1, unsigned short IN2, 
		          unsigned short EnablePinB, unsigned short IN3, unsigned short IN4);
   L298N_Jetson(unsigned short IN1, unsigned short IN2, 
		          unsigned short IN3, unsigned short IN4);
   // L298N_Jetson(std::shared_ptr<GPIO::PWM> drive[], int IN1, int IN2, int IN3, int IN4, bool setup);
   
   // 一些用来控制电机的函数
   void setSpeed(const unsigned short pwmVal);
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