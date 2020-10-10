cmake_minimum_required(VERSION 3.16)
project(TextToImage)

set(CMAKE_CXX_STANDARD 17)

add_executable(TextToImage tti.cpp tti.h bmp.h bmp.cpp main.cpp)