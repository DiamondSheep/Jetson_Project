
project(handler)

include_directories("../driver")

add_library(handler handler.cpp)

target_link_libraries(handler driver)
target_include_directories(handler PRIVATE "../driver")

# no need for including JetsonGPIO here