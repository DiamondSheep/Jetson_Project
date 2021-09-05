#include "face_detection.hpp"
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

#define MIN_ERROR 5

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

int pixel2angle_X(int pixel, int size){
	return int(0.28 * 62.2 * pixel / size);
}

int pixel2angle_Y(int pixel, int size){
	return int(0.195 * 48.8 * pixel / size);
}

int main(){

        driver machine(1); // bus 1 of Jetson Nano
        //servo.angle(n, angle); // n=0 for bottom; n=1 for top;
	
	// machine.angle(1, 90);
	// machine.angle(0, 90);

	machine.forward();
	for (int i = 0; i != 10; i++){
		machine.set_speed(100 * i + 500);
        	// machine.forward();
		std::cout << "Speed: " <<  100 * i + 500 << std::endl;
		sleep(1);
	}
	
	machine.stop();	
        
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


        // face_detect(pipeline);

        std::cout << "Test done." << std::endl;
        return 0;
}


void face_detect(std::string pipeline){
        driver servo(1); // bus 1 of Jetson Nano

	cv::CascadeClassifier face_cascade = cv::CascadeClassifier(
                       "/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml"
                        );

        cv::VideoCapture cap(pipeline, cv::CAP_GSTREAMER);
        if (!cap.isOpened()){
                std::cout << "Failed to open camera " << std::endl;
                return;
        }
        cv::namedWindow("Face Detection", cv::WINDOW_AUTOSIZE);
        cv::Mat frame;
	while(true){
                if (!cap.read(frame)){
                        std::cout << "Capture read error " << std::endl;
                        break;
                }
                // Drawing center point of the frame
                cv::Point center(frame.size[1] / 2, frame.size[0] / 2);
                cv::circle(frame, center, 2, cv::Scalar(0, 0, 255), 2);

                cv::Mat gray_frame;
                cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY); // Convert to gray image

                std::vector<cv::Rect> faces;
                auto start = clock();
                face_cascade.detectMultiScale(gray_frame, faces, 1.3, 5);
                auto end = clock();

                std::cout << "Detect Time: " << double(end - start)/CLOCKS_PER_SEC << "s"
                          << " | Frame size: (" << frame.size[1] << ", " << frame.size[0] << ")" << std::endl;
	
		for (auto i = 0; i < faces.size(); i++){
                        cv::Point face_center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2);
                        cv::circle(frame, face_center, 2, cv::Scalar(255, 255, 255), 2);
                        std::cout << "\tface center: " << faces[i].x + faces[i].width/2 << ", "
                                                       << faces[i].y + faces[i].height/2 << std::endl;
                        std::cout << "\tdistance: x(" << face_center.x - center.x
                                           << "), y(" << face_center.y - center.y << "). " << std::endl;
                        // Tracking
                        int angle_X, angle_Y;

                        if ((center.x - face_center.x > MIN_ERROR) || (face_center.x - center.x > MIN_ERROR)){
                                angle_X = pixel2angle_X(center.x - face_center.x, frame.size[1]);
                                servo.angle(0, servo.bottom_angle + angle_X);
                        }

                        if ((face_center.y - center.y > MIN_ERROR) || (center.y - face_center.y > MIN_ERROR)){
                                angle_Y = pixel2angle_Y(center.y - face_center.y, frame.size[0]);
                                servo.angle(1, servo.top_angle - angle_Y);
                        }

                        cv::Point p1(faces[i].x, faces[i].y);
                        cv::Point p2(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
                        cv::rectangle(frame, p1, p2, cv::Scalar(120, 120, 255), 4);

                        // cv::Mat faceROI = gray_frame(faces[i]);
                }
		cv::imshow("Face Detection", frame);
                int keycode = cv::waitKey(20) && 0xff;
                if (keycode == 27) break; // close the window when pressing ESC

        }
        cap.release();
        cv::destroyAllWindows();

}

