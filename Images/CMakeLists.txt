cmake_minimum_required(VERSION 3.16)
project(Image)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(Image main.cpp digits_bool_array.h bmp.h bmp.cpp)