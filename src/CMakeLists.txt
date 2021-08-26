
include_directories(${MyProject_SOURCE_DIR}/include)
include_directories(${MyProject_SOURCE_DIR}/JHPWMPCA9685/include)
link_directories(${MyProject_SOURCE_DIR}/JHPWMPCA9685/src)

add_executable(face_detection face_detection.cpp)

target_link_libraries(face_detection )
