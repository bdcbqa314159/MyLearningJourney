cmake_minimum_required(VERSION 3.0.0)

message("Hello World")

# set(NAME "B. COHEN") -> string NAME = B. COHEN
# set(NAME B. COHEN) -> list NAME = B.;COHEN

# list() string() -> list and string variables

set(NAME "Bob Smith")
set(HEIGHT 190)
set(AGE 5)

message("Hello, my name is ${NAME}, my height is ${HEIGHT} cm and I am ${AGE}
years old.")

message("Playing with the variables")
message("set(VAR aa bb cc)")
set(VAR aa bb cc)
message(${VAR})
message("${VAR}")
message("======================")
message("set(VAR aa;bb;cc)")
set(VAR aa;bb;cc)
message(${VAR})
message("${VAR}")
message("======================")
message("set(VAR "aa" "bb" "cc")")
set(VAR "aa" "bb" "cc")
message(${VAR})
message("${VAR}")
message("======================")
message("set(VAR "aa bb cc")")
set(VAR "aa bb cc")
message(${VAR})
message("${VAR}")
message("======================")
message("set(VAR "aa;bb;cc")")
set(VAR "aa;bb;cc")
message(${VAR})
message("${VAR}")

message("Playing with variable part 2:")
set(NAME Alice)
set(Alice Bob)

message(${NAME})
message(${${NAME}})
message(NAME ${NAME} ${${NAME}})
message(NAME${NAME}${${NAME}})
message("NAME ${NAME} ${${NAME}}")

set(NAMEAliceBob Charlie)
message(${NAME${NAME}${${NAME}}})

# Every variable in CMake is a string

# Not the same:
# Variable ${VAR}
# Generator Expressions $<TARGET_FILE:library>
message("\n==============")
message("Lists and strings")
message("==============\n")
set(VAR a b c;d "e;f" 2.7 "Hello There")
message("Original VAR: ${VAR}")

list(APPEND VAR 1.6 XX)
message(${VAR})

list(REMOVE_AT VAR 2 -3)
message(${VAR})

list(REMOVE_ITEM VAR a 2.7)
message(${VAR})

list(INSERT VAR 2 XX 2.7)
message(${VAR})

list(REVERSE VAR)
message(${VAR})

list(REMOVE_DUPLICATES VAR)
message(${VAR})

list(SORT VAR)
message(${VAR})

message("\n==================")
message("Lists and strings")
message("==================\n")

list(LENGTH VAR len_var)
list(GET VAR 2 5 6 sub_list)
list(SUBLIST VAR 2 3 sub_list2)
list(JOIN VAR ++ str_list)
list(FIND VAR XX find_var)

message("len_var: ${len_var}")
message("sub_list: ${sub_list}")
message("sub_list2: ${sub_list2}")
message("str_list: ${str_list}")
message("find_var: ${find_var}")
