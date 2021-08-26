cmake_minimum_required(VERSION 3.2)
project(run)

set(sources main.cpp L298N_Jetson.cpp)
add_executable(run ${sources})
find_library(lib JetsonGPIO)
target_link_libraries(run ${lib})
