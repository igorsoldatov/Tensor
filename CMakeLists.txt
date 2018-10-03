cmake_minimum_required(VERSION 3.10)
project(tensor)

set(CMAKE_CXX_STANDARD 11)

add_executable(tensor main.cpp tensor.cpp tensor.hpp)