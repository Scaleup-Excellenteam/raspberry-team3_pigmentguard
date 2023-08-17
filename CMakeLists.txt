cmake_minimum_required(VERSION 3.22)
project(PigmentGuard)

set(CMAKE_CXX_STANDARD 14)

add_executable(PigmentGuard main.cpp Controller.cpp Controller.h ImageProcessing.cpp ImageProcessing.h)

find_package(OpenCV REQUIRED)
target_link_libraries(PigmentGuard PRIVATE ${OpenCV_LIBS})