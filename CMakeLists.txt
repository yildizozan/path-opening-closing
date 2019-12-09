cmake_minimum_required(VERSION 3.15)
project(path_opening_closing)

set(CMAKE_CXX_STANDARD 11)

find_package( OpenCV REQUIRED )

add_executable(path_opening_closing main.cpp BPathOpening.cpp BPathOpening.h)

target_link_libraries( path_opening_closing ${OpenCV_LIBS} )