cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Calculator_Project VERSION 1.0.0)

add_subdirectory(my_math)
add_subdirectory(my_print)

add_executable(calculator
main.cpp)

# PUBLIC INTERFACE PRIVATE
target_link_libraries(calculator my_math my_print)
message("CMAKE INSTALL PREFIX: ${CMAKE_INSTALL_PREFIX}")
