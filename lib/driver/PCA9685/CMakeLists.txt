
project(PCA9685)

add_library(PCA9685 PCA9685.cpp)
target_link_libraries(PCA9685 PUBLIC i2c)
target_include_directories(PCA9685 PUBLIC "usr/include/i2c")
