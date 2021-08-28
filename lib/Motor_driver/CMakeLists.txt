
project(motor_driver)

add_library(motor_driver motor_driver.cpp)

target_link_libraries(motor_driver PUBLIC "/usr/local/lib/libJetsonGPIO.a")
target_include_directories(motor_driver PUBLIC "/usr/local/include")

