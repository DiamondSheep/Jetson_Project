
#include "definitions.h"
#include "motor_driver.hpp"
#include <unistd.h>
#include <iostream>

int main(int argc, char** argv) {

    motor_driver motors(JETSON_ENA_PIN, JETSON_IN1_PIN, JETSON_IN2_PIN, 
                        JETSON_ENB_PIN, JETSON_IN3_PIN, JETSON_IN4_PIN);
     
    while (true){
        motors.forward();
        std::cout << "Driving Forward " << std::endl;
        motors.run();
	usleep(3000000);

	motors.backward();
	std::cout << "Driving Backward " << std::endl;
	motors.run();
	usleep(3000000);

	motors.stop();	
        break;
    }
    return 0;
}


