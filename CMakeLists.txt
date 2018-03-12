cmake_minimum_required(VERSION 3.8)
project(cg1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp color.cpp rgbimage.cpp vector.cpp CGUtilities.cpp Camera.cpp Camera.h SimpleRayTracer.cpp SimpleRayTracer.h)
add_executable(cg1 ${SOURCE_FILES})