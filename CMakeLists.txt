cmake_minimum_required(VERSION 3.10)

project(face_detection) # for face detection and tracking

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(lib)
# include driver library
list(APPEND EXTRA_LIBS driver)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/lib/driver")

# include opencv library
find_package( OpenCV REQUIRED )
list(APPEND EXTRA_LIBS ${OpenCV_LIBS})
list(APPEND EXTRA_INCLUDES ${OpenCV_DIRS})

list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/include")

set(sources "${PROJECT_SOURCE_DIR}/src/${CMAKE_PROJECT_NAME}.cpp")
set(CMAKE_CXX_FLAGS "-g -pthread")
add_executable(${CMAKE_PROJECT_NAME} ${sources})

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${EXTRA_LIBS})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR} 
						     ${EXTRA_INCLUDES}
						     )
