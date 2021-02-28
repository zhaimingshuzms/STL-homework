cmake_minimum_required(VERSION 3.16.3)
project(vector)

set(CMAKE_CXX_STANDARD 20)

add_executable(vector main.cpp exceptions.hpp utility.hpp vector.hpp class-bint.hpp class-integer.hpp class-matrix.hpp)