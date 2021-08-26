
#include "definitions.h"
#include "L298N_Jetson.hpp"
#include <unistd.h>
#include <iostream>

int main(int argc, char** argv) {

    L298N_Jetson motors(JETSON_ENA_PIN, JETSON_IN1_PIN, JETSON_IN2_PIN, 
                        JETSON_ENB_PIN, JETSON_IN3_PIN, JETSON_IN4_PIN);
     
    while (true){
        motors.forward();
        std::cout << "Driving Forward " << std::endl;
        motors.run();
	usleep(3000000);
	/*
        for (unsigned short i=0; i < 255; i++){
            motors.setSpeed(i/2.6);
	    usleep(10000);
        }
	*/
	motors.backward();
	std::cout << "Driving Backward " << std::endl;
	motors.run();
	usleep(3000000);

	motors.stop();	
        break;
    }
    return 0;
}


