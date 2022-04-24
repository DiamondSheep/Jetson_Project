#ifndef _DRIVER_H
#define _DRIVER_H

#include <memory>
#include <JetsonGPIO.h>
#include "PCA9685/PCA9685.hpp"

class driver{
public:
    driver();
    ~driver();

    void angle(const int channel, const int angle);
    int top_angle = 90, bottom_angle = 90;

private:

    std::shared_ptr<PCA9685> PWMdirver;
    // settings for PCA9685
    int bus = 1; // bus 1 (pin 3 and pin 5)
    int address = 0x40;
    int frequency = 50; // default 50 Hz
    
    // Calibrated for SG-90 servo (top of the pan-tilt) and MG-90S servo (bottom of the pan-tilt)
    int servoMin = 112; // 150 for the SG-90 on the top of the pan-tilt
    int servoMax = 484; // 336 for the SG-90 on the top of the pan-tilt
    int servoMiddle = 298;

    // map degrees to the servo value
    int map (const int degree) const;

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
