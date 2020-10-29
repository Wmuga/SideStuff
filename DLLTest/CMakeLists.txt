cmake_minimum_required(VERSION 3.16)
project(DLLTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(DLLTest nDll.cpp nDll.h)