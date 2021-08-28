
project(JHPWMPCA9685)

add_library(JHPWMPCA9685 JHPWMPCA9685.cpp)
target_link_libraries(JHPWMPCA9685 PUBLIC i2c)
target_include_directories(JHPWMPCA9685 PUBLIC "usr/include/i2c")
