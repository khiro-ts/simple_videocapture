cmake_minimum_required(VERSION 3.1)

project(simple_videocapture CXX)

add_executable(simple_videocapture main.cpp)

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    target_include_directories(simple_videocapture PUBLIC ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(simple_videocapture ${OpenCV_LIBS})
endif()
