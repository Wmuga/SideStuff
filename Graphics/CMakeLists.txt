cmake_minimum_required(VERSION 3.16)
project(Graphics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(Graphics main.cpp)