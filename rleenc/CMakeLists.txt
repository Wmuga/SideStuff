cmake_minimum_required(VERSION 3.16)
project(rleenc)

set(CMAKE_CXX_STANDARD 17)

add_executable(rleenc main.cpp rle.cpp rle.h)