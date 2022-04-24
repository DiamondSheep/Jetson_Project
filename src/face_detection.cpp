#include "face_detection.hpp"
#include <iostream>

int main(){

        driver machine; // bus 1 of Jetson Nano
        //servo.angle(n, angle); // n=0 for bottom; n=1 for top;
	
	// machine.angle(1, 90);
	// machine.angle(0, 90);

	// settings for capture and display
        // which should be move to the definition later
        int capture_width = 1280; // Max 3280
        int capture_height = 720; // Max 2464
        int display_width = 640;
        int display_height = 360;
        int framerate = 10;
        int flip_method = 0;

        std::string pipeline = gstreamer_pipeline(capture_width,
                                         capture_height,
                                         display_width,
                                         display_height,
                                         framerate,
                                         flip_method);


        face_detect(pipeline);

        std::cout << "Test done." << std::endl;
        return 0;
}



