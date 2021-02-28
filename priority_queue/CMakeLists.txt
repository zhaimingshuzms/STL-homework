cmake_minimum_required(VERSION 3.16.3)
project(priority_queue)

set(CMAKE_CXX_STANDARD 20)

add_executable(priority_queue main.cpp priority_queue.hpp exceptions.hpp utility.hpp)