
project(servo_driver)
add_subdirectory(JHPWMPCA9685)

add_library(servo_driver servo_driver.cpp)

target_link_libraries(servo_driver PRIVATE JHPWMPCA9685)
target_include_directories(servo_driver PRIVATE "${PROJECT_SOURCE_DIR}/lib/Servo_driver/JHPWMPCA9685")
