#ifndef _DRIVER_H
#define _DRIVER_H

#include <memory>
#include <JetsonGPIO.h>
#include "PCA9685/PCA9685.hpp"

class driver{
public:
    driver(int bus=1, int address=0x40, int frequency=50);
    ~driver();

    void set_top_angle(const int angle){
        top_angle = angle;
        int value = _map(angle);
        if (value <= _topServoMin || value >= _topServoMax){
            printf("Out of top angle range.\n");
            return;
        }
        _PWMdirver->setPWM(1, 0, value);
    }
    void set_bottom_angle(const int angle){
        bottom_angle = angle;
        int value = _map(angle);
        if (value <= _servoMin    || value >= _servoMax){
            printf("Out of bottom angle range.\n");
	        return;
        }
        _PWMdirver->setPWM(0, 0, value);
    }
    const int get_top_angle() const{
        return top_angle;
    }
    const int get_bottom_angle() const{
        return bottom_angle;
    }

private:

    std::shared_ptr<PCA9685> _PWMdirver;
    // settings for PCA9685
    int _bus = 1; // bus 1 (pin 3 and pin 5)
    int _address = 0x40;
    int _frequency = 50; // default 50 Hz
    
    // Calibrated for SG-90 servo (top of the pan-tilt) 
    // and MG-90S servo (bottom of the pan-tilt)
    const int _servoMin = 112; // 150 for the SG-90 on the top of the pan-tilt
    const int _servoMax = 484; // 336 for the SG-90 on the top of the pan-tilt
    const int _topServoMin = 150;
    const int _topServoMax = 336;
    const int _servoMiddle = 298;

    int top_angle = 90, bottom_angle = 90;

    void _angle(const int channel, const int angle);
    // map degrees to the servo value
    int _map (const int degree) const;
};

#endif
