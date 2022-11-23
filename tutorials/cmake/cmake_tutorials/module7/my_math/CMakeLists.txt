add_library(my_math
src/addition.cpp
src/soustraction.cpp)

target_include_directories(my_math PUBLIC include)
