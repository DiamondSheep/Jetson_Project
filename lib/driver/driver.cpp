#include "driver.hpp"

driver::driver() = default;

driver::driver(int bus, int address){
    PWMdirver = std::make_shared<PCA9685>(address, bus);   
    PWMdirver->openPCA9685();
    printf("PCA9685 Device Address: 0x%02X\n", PWMdirver->kI2CAddress);
    PWMdirver->setAllPWM(0, 0);
    PWMdirver->reset();
    PWMdirver->setPWMFrequency(frequency);
    //SERVO INITIAL
    this->angle(0, 90);
    this->angle(1, 90);
    //MOTOR INITIAL
    speed_left = 0;
    speed_right = 0;
    GPIO::setmode(GPIO::BOARD);
    GPIO::setup(IN1, GPIO::OUT, GPIO::LOW);
    GPIO::setup(IN2, GPIO::OUT, GPIO::LOW);
    GPIO::setup(IN3, GPIO::OUT, GPIO::LOW);
    GPIO::setup(IN4, GPIO::OUT, GPIO::LOW);
    GPIO::setup(READ_A1, GPIO::IN);
    GPIO::setup(READ_B1, GPIO::IN);
    GPIO::setup(READ_A2, GPIO::IN);
    GPIO::setup(READ_B2, GPIO::IN);
}

driver::~driver(){
    this->angle(0, 90);
    this->angle(1, 100);
    this->stop();
    GPIO::cleanup(IN1);
    GPIO::cleanup(IN2);
    GPIO::cleanup(IN3);
    GPIO::cleanup(IN4);
    GPIO::cleanup(READ_A1);
    GPIO::cleanup(READ_A2);
    GPIO::cleanup(READ_B1);
    GPIO::cleanup(READ_B2);
    PWMdirver->closePCA9685();
}

// servo
void driver::angle(int channel, int angle){
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

// motor
void driver::forward(){
    GPIO::setup(IN1, GPIO::OUT, GPIO::LOW);
    GPIO::setup(IN2, GPIO::OUT, GPIO::HIGH);
    GPIO::setup(IN3, GPIO::OUT, GPIO::LOW);
    GPIO::setup(IN4, GPIO::OUT, GPIO::HIGH);
    this->run();
}
void driver::backward(){
    GPIO::setup(IN1, GPIO::OUT, GPIO::HIGH);
    GPIO::setup(IN2, GPIO::OUT, GPIO::LOW);
    GPIO::setup(IN3, GPIO::OUT, GPIO::HIGH);
    GPIO::setup(IN4, GPIO::OUT, GPIO::LOW);
    this->run();
}

void driver::run(){
    PWMdirver->setPWM(2, 0, speed_right); // right
    PWMdirver->setPWM(3, 0, speed_left); // left
    // speed range from 0 to 4095
}

void driver::stop(){
    GPIO::setup(IN1, GPIO::OUT, GPIO::LOW);
    GPIO::setup(IN2, GPIO::OUT, GPIO::LOW);
    GPIO::setup(IN3, GPIO::OUT, GPIO::LOW);
    GPIO::setup(IN4, GPIO::OUT, GPIO::LOW);
    PWMdirver->setPWM(3, 0, 0);
    PWMdirver->setPWM(4, 0, 0);
}

void driver::set_speed(int val){
    speed_right = val;
    speed_left = val;
    this->run();
}

// private
int driver::map (int degree) {
    if (degree >= 0 && degree <= 180)
        return (degree * (servoMax-servoMin)/180 + servoMin);
    else {
	printf("Out of angle range.\n");
	return servoMiddle;
    }
}

