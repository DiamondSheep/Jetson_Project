
#include "motor_driver.hpp"

motor_driver::motor_driver() = default;

motor_driver::~motor_driver() { 
    this->Drive_PWM_left->stop();
    this->Drive_PWM_right->stop();
    if (this->setup){
        GPIO::cleanup();
    }
};

motor_driver::motor_driver(unsigned short EnablePinA, 
			               unsigned short IN1, 
			               unsigned short IN2, 
			               unsigned short EnablePinB, 
			               unsigned short IN3, 
			               unsigned short IN4) {
    // setting the motor
    this->EN[0] = EnablePinA;
    this->left[0] = IN1;
    this->left[1] = IN2;

    this->EN[1] = EnablePinB;
    this->right[0] = IN3;
    this->right[1] = IN4;
    
    this->pwmVal = 0;
    // 设置GPIO的模式（应该是对的）
    GPIO::setmode(GPIO::BOARD);
    // setting the level
    //设置电平
    GPIO::setup(this->EN[0], GPIO::OUT, GPIO::HIGH);
    GPIO::setup(this->left[0], GPIO::OUT,GPIO::LOW);
    GPIO::setup(this->left[1], GPIO::OUT,GPIO::LOW);

    GPIO::setup(this->EN[1], GPIO::OUT, GPIO::HIGH);
    GPIO::setup(this->right[0], GPIO::OUT,GPIO::LOW);
    GPIO::setup(this->right[1], GPIO::OUT,GPIO::LOW);
    // 设置 pwm 驱动
    this->Drive_PWM_left = std::make_shared<GPIO::PWM>(this->EN[0], 10000);
    this->Drive_PWM_right = std::make_shared<GPIO::PWM>(this->EN[1], 10000);

    this->setup = true;
}

motor_driver::motor_driver(unsigned short IN1, 
			               unsigned short IN2, 
			               unsigned short IN3, 
			               unsigned short IN4) {
    // initialization without enable pin
    this->left[0] = IN1;
    this->left[1] = IN2;
    this->right[0] = IN3;
    this->right[1] = IN4;

    this->pwmVal = 0;

    GPIO::setmode(GPIO::BOARD);
    GPIO::setup(this->left[0], GPIO::OUT,GPIO::LOW);
    GPIO::setup(this->left[1], GPIO::OUT,GPIO::LOW);
    GPIO::setup(this->right[0], GPIO::OUT,GPIO::LOW);
    GPIO::setup(this->right[1], GPIO::OUT,GPIO::LOW);
    
    this->setup = true;
}

/*
motor_driver::motor_driver(std::shared_ptr<GPIO::PWM> drive[], int IN1, int IN2, int IN3, int IN4, bool setup){
    // initialization with a given PWM
    this->Drive_PWM = drive;

    this->left[0] = IN1;
    this->left[1] = IN2;
    this->right[0] = IN3;
    this->right[1] = IN4;

    this->pwmVal = 0;

    GPIO::setup(this->left[0], GPIO::OUT,GPIO::LOW);
    GPIO::setup(this->left[1], GPIO::OUT,GPIO::LOW);
    GPIO::setup(this->right[0], GPIO::OUT,GPIO::LOW);
    GPIO::setup(this->right[1], GPIO::OUT,GPIO::LOW);

    this->setup = false; // this tells the object we didn't create the PWM object and thus can't destroy it or stop PWM
                        // The argument doesn't matter, we have to have another argument so the override doesn't collide with
                        // the other constructor
}
*/

void motor_driver::setSpeed(const unsigned short pwmVal){
    this->pwmVal = pwmVal;
}

const unsigned short motor_driver::getSpeed(){
    return this->pwmVal;
}

void motor_driver::forward(){
    GPIO::setup(this->left[0], GPIO::OUT,GPIO::HIGH);
    GPIO::setup(this->left[1], GPIO::OUT,GPIO::LOW);
    GPIO::setup(this->right[0], GPIO::OUT,GPIO::LOW);
    GPIO::setup(this->right[1], GPIO::OUT,GPIO::HIGH);

    run();
}
void motor_driver::backward(){
    GPIO::setup(this->left[0], GPIO::OUT,GPIO::LOW);
    GPIO::setup(this->left[1], GPIO::OUT,GPIO::HIGH);
    GPIO::setup(this->right[0], GPIO::OUT,GPIO::HIGH);
    GPIO::setup(this->right[1], GPIO::OUT,GPIO::LOW);

    run();
}


void motor_driver::run(){
    this->Drive_PWM_left->ChangeDutyCycle( (this->pwmVal) / 255.0 );
    this->Drive_PWM_right->ChangeDutyCycle( (this->pwmVal) / 255.0 );
    //this->Drive_PWM_left->start(this->pwmVal);
    //this->Drive_PWM_right->start(this->pwmVal);
    //important -- you need to send in values from [0, 100].  These are a percentage
    //a percentage for the GPIO library
}

void motor_driver::stop(){
    GPIO::setup(this->left[0], GPIO::OUT,GPIO::LOW);
    GPIO::setup(this->left[1], GPIO::OUT,GPIO::LOW);
    GPIO::setup(this->right[0], GPIO::OUT,GPIO::LOW);
    GPIO::setup(this->right[1], GPIO::OUT,GPIO::LOW);
    this->Drive_PWM_left->stop();
    this->Drive_PWM_right->stop();
}
