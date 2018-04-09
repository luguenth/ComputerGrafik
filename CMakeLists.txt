cmake_minimum_required(VERSION 3.8)
project(cg1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Color.cpp Color.h RGBImage.cpp RGBImage.h Vector.cpp Vector.h CGUtilities.cpp Camera.cpp Camera.h SimpleRayTracer.cpp SimpleRayTracer.h)

find_package(glfw3 REQUIRED)

add_executable(cg1 ${SOURCE_FILES})

target_link_libraries(glfw)