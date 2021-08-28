#include "face_detection.hpp"
#include <time.h>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

std::string gstreamer_pipeline (int capture_width, int capture_height, 
				int display_width, int display_height, 
				int framerate, int flip_method) {
    return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + 
	   std::to_string(capture_width) + 
	   ", height=(int)" +
           std::to_string(capture_height) + 
	   ", format=(string)NV12, framerate=(fraction)" + 
	   std::to_string(framerate) +
           "/1 ! nvvidconv flip-method=" + 
	   std::to_string(flip_method) + 
	   " ! video/x-raw, width=(int)" + 
	   std::to_string(display_width) + 
	   ", height=(int)" +
           std::to_string(display_height) + 
	   ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

int main(){
	motor_driver motor(JETSON_ENA_PIN, JETSON_IN1_PIN, JETSON_IN2_PIN,
                           JETSON_ENB_PIN, JETSON_IN3_PIN, JETSON_IN4_PIN);
	// motor.run();
	// motor.forward();
	// motor.backward();
	// motor.setSpeed(const unsigned short pwmVal);
   	// motor.getSpeed();
	// motor.stop();
	
	servo_driver servo(1); // bus 1 of Jetson Nano
    	// servo.angle(n, angle); // n=0 for bottom; n=1 for top;
	
	// settings for capture and display
	// which should be move to the definition later
	int capture_width = 1280;
	int capture_height = 720;
	int display_width = 1280;
	int display_height = 720;
	int framerate = 60;
	int flip_method = 2;

	std::string pipeline = gstreamer_pipeline(capture_width, 
					 capture_height, 
					 display_width, 
					 display_height,
					 framerate, 
					 flip_method); 

	std::cout << "Using pipeline: \n\t" << pipeline << std::endl;
	cv::VideoCapture cap(pipeline, cv::CAP_GSTREAMER);
	if (!cap.isOpened()){
		std::cout << "Failed to open camera " << std::endl;
		return (-1);
	}
	cv::namedWindow("CSI Camera", cv::WINDOW_AUTOSIZE);
	cv::Mat img;
	
	while(true){
		if (!cap.read(img)){
			std::cout << "Capture read error " << std::endl;
			break;
		}
		cv::imshow("CSI Camera", img);
		int keycode = cv::waitKey(20) && 0xff;
		if (keycode == 27) break; // close the window when pressing ESC
	}
	cap.release();
	cv::destroyAllWindows();

	std::cout << "Test done." << std::endl;
	return 0;
}
