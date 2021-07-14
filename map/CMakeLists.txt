cmake_minimum_required(VERSION 3.16.3)
project(map)

set(CMAKE_CXX_STANDARD 20)

add_executable(map main.cpp map.hpp utility.hpp exceptions.hpp)