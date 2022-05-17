#include "driver.hpp"

driver::driver(int bus, int address, int frequency)
    : _bus(bus), _address(address), _frequency(frequency){
    GPIO::setwarnings(true);
    _PWMdirver = std::make_shared<PCA9685>(_address, _bus);   
    _PWMdirver->openPCA9685();
    // printf("PCA9685 Device Address: 0x%02X, Frequency: %d Hz\n", PWMdirver->kI2CAddress, frequency);
    _PWMdirver->setAllPWM(0, 0);
    _PWMdirver->reset();
    _PWMdirver->setPWMFrequency(_frequency);
    //SERVO INITIAL
    _angle(0, 90);
    _angle(1, 90);
}

driver::~driver(){
    _angle(0, 90);
    _angle(1, 100);
    _PWMdirver->closePCA9685();
}

// servo
void driver::_angle (const int channel, const int angle){
    int value = _map(angle);
    // Check angle range
    if ((channel == 1 && (value <= _topServoMin || value >= _topServoMax)) 
     || (channel == 0 && (value <= _servoMin    || value >= _servoMax))){
	    printf("Out of angle range.\n");
	    return;
	}
    _PWMdirver->setPWM(channel, 0, value);
}

// private
int driver::_map (const int degree) const{
    if (degree >= 0 && degree <= 180)
        return (degree * (_servoMax - _servoMin) / 180 + _servoMin);
    else {
        printf("Out of angle range.\n");
        return _servoMiddle;
    }
}

