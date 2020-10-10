cmake_minimum_required(VERSION 3.16)
project(aeed)

set(CMAKE_CXX_STANDARD 17)

add_executable(aeed main.cpp ae_coder.cpp ae_coder.h)