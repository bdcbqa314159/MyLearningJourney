add_library(my_math
src/addition.cpp
src/soustraction.cpp)

target_include_directories(my_math PUBLIC include)
# I already worked with the install command in a better way than showed in the tutorial.
