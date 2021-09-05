#ifndef _SERVO_H
#define _SERVO_H

#include <memory>
#include <JetsonGPIO.h>
#include "JHPWMPCA9685/JHPWMPCA9685.hpp"

class driver{
public:
    // Calibrated for SG-90 servo (top of the pan-tilt) and MG-90S servo (bottom of the pan-tilt)
    int servoMin = 112; // 150 for the SG-90 on the top of the pan-tilt
    int servoMax = 484; // 336 for the SG-90 on the top of the pan-tilt
    int servoMiddle = 298;
    
    int bus = 1; // bus 1 (pin 3 and pin 5)
    int address = 0x40;
    int frequency = 50; // default 50 Hz

    int top_angle = 90, bottom_angle = 90;
    int speed_left = 0;
    int speed_right = 0;

    std::shared_ptr<PCA9685> PWMdirver;

    driver();
    driver(int bus=1, int address=0x40);
    ~driver();

    void init();
    void angle(int channel, int angle);
    void forward();
    void backward();
    void run();
    void stop();
    void set_speed(int);

private:
    // map degrees to the servo value
    int map(int degree);
    unsigned short IN1=35;
    unsigned short IN2=36;
    unsigned short IN3=37;
    unsigned short IN4=38;

    unsigned short READ_A1=21;
    unsigned short READ_B1=22;
    unsigned short READ_A2=23;
    unsigned short READ_B2=24;
};

#endif
