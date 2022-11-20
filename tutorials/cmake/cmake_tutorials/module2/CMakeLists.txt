cmake_minimum_required(VERSION 3.24)

project(Calculator_Project VERSION 1.0.0)

add_library(my_math
addition.cpp
soustraction.cpp)

add_library(my_print
printer.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(calculator
main.cpp)

target_link_libraries(calculator my_math my_print)
