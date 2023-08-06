cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(lab8)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(task2 task2.cpp)
target_link_libraries(task2 ${OpenCV_LIBS})

