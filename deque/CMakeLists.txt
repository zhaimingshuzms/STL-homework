cmake_minimum_required(VERSION 3.17)
project(deque)

set(CMAKE_CXX_STANDARD 20)

add_executable(deque main.cpp deque.hpp list.hpp exceptions.hpp utility.hpp class-bint.hpp class-matrix.hpp class-integer.hpp)