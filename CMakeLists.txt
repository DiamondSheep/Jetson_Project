set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

cmake_minimum_required(VERSION 3.10)
project(face_detection)

# include servo driver library
add_subdirectory(Servo_driver)
list(APPEND EXTRA_LIBS servo_driver)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/Servo_driver")

# include opencv library
list(APPEND EXTRA_LIBS opencv2)
list(APPEND EXTRA_INCLUDES "/usr/include/opencv2")

set(sources face_detection.cpp)

add_executable(face_detection ${sources})

target_link_libraries(face_detection PUBLIC ${EXTRA_LIBS})
target_include_directories(face_detection PUBLIC ${EXTRA_INCLUDES})
