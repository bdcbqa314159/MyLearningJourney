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

# set(A "123" CACHE STRING "This command sets variable A in persistent cache")
# message($CACHE{A})

# set(ENV <variable_name> <name_value>)
# message($ENV{variable_name})

# set(Name Alice CACHE STRING "The name variable")
# # set(Name Bob CACHE STRING "The modified name variable" FORCE) - Not recommended
# # set(Name Bob CACHE STRING "The modified name variable")
# message($CACHE{Name})

# message(CMAKE_VERSION=${CMAKE_VERSION})
#
# message("Root level CMakeLists: CMAKE_PROJECT_NAME=${CMAKE_PROJECT_NAME}")
# message("Root level CMakeLists: PROJECT_NAME=${PROJECT_NAME}")

#Check about generators here we only be focussed on cmake generator.
