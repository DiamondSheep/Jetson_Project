#include "face_detection.hpp"
#include <time.h>
#include <iostream>

int main(){
	servo_driver servo(1);
    	servo.angle(0, 45);
    	sleep(1);
    	servo.angle(0, 135);
    	sleep(1);
	servo.angle(0, 90);
	sleep(1);
    	servo.angle(1, 20);
	sleep(1);
	servo.angle(1, 90);
    	
	std::cout << "Servo test done." << std::endl;
	return 0;
}
