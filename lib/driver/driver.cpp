#include "driver.hpp"

driver::driver(){
    GPIO::setwarnings(true);
    PWMdirver = std::make_shared<PCA9685>(address, bus);   
    PWMdirver->openPCA9685();
    printf("PCA9685 Device Address: 0x%02X, Frequency: %d Hz\n", PWMdirver->kI2CAddress, frequency);
    PWMdirver->setAllPWM(0, 0);
    PWMdirver->reset();
    PWMdirver->setPWMFrequency(frequency);
    //SERVO INITIAL
    this->angle(0, 90);
    this->angle(1, 90);
}

driver::~driver(){
    this->angle(0, 90);
    this->angle(1, 100);
    PWMdirver->closePCA9685();
}

// servo
void driver::angle(const int channel, const int angle){
    if (channel == 0)
	bottom_angle = angle;
    if (channel == 1)
	top_angle = angle;
    int value = this->map(angle);
    if ((channel == 1 && (value <= 112 || value >= 336)) || 
	(channel == 0 && (value <= servoMin || value >= servoMax))){
	    printf("Out of angle range.\n");
	    return;
	}
    PWMdirver->setPWM(channel, 0, value);
}

// private
int driver::map (const int degree) const{
    if (degree >= 0 && degree <= 180)
        return (degree * (servoMax-servoMin)/180 + servoMin);
    else {
	printf("Out of angle range.\n");
	return servoMiddle;
    }
}

