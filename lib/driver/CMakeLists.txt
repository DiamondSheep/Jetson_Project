
project(driver)
add_subdirectory(JHPWMPCA9685)

add_library(driver driver.cpp)

target_link_libraries(driver PUBLIC "/usr/local/lib/libJetsonGPIO.a")
target_include_directories(driver PUBLIC "/usr/local/include")

target_link_libraries(driver PRIVATE JHPWMPCA9685)
target_include_directories(driver PRIVATE "${PROJECT_SOURCE_DIR}/JHPWMPCA9685")
