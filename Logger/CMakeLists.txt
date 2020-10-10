cmake_minimum_required(VERSION 3.16)
project(Logger)

set(CMAKE_CXX_STANDARD 17)

add_executable(Logger main.cpp logger.cpp logger.h)