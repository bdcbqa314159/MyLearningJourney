cmake_minimum_required(VERSION 3.0.0)

set(VAR YES)

if (VAR)
	message("If block executed")
else()
	message("Else block executed")
endif()

message("=====Next try=======")
set(VAR "")

if (VAR)
	message("If block executed")
else()
	message("Else block executed")
endif()

message("=====Next try=======")
set(VAR OFF)
set(VAR2 VAR)

if (VAR2)
	message("If block executed")
else()
	message("Else block executed")
endif()

message("=====Next try=======")
set(VAR OFF)
set(VAR2 VAR)

if (${VAR2})
	message("If block executed")
else()
	message("Else block executed")
endif()

message("=====Another test=======")

set(Name Alice)

if (DEFINED Name)
	message("Name: if block executed")
else()
	message("Name: else block executed")
endif()


if (DEFINED Age)
	message("Age: if block executed")
else()
	message("Age: else block executed")
endif()

message("=====Another test=======")

if (COMMAND target_link_library)
	message("target_link_library: if block executed")
else()
	message("target_link_library: else block executed")
endif()


if (COMMAND target_link_libraries)
	message("target_link_libraries: if block executed")
else()
	message("target_link_libraries: else block executed")
endif()


if (EXISTS /Users/bernardocohen/repos/MyLearningJourney/tutorials/cmake/cmake_tutorials/module5/CMakeLists.txt)
	message("path if block executed")
else()
message("path: else block executed")
endif()

message("=====Binary test=======")
set(Name1 Alice)
set(Name2 Bob)

if(Name1 STRLESS Name2)
	message("${Name1} is less than ${Name2}")
elseif(Name1 STRGREATER Name2)
	message("${Name1} is greater than ${Name2}")
elseif(Name1 STREQUAL Name2)
	message("${Name1} is equal to ${Name2}")
endif()

set(Name1 Charlie)
set(Name2 bob)

if(Name1 STRLESS Name2)
	message("${Name1} is less than ${Name2}")
elseif(Name1 STRGREATER Name2)
	message("${Name1} is greater than ${Name2}")
elseif(Name1 STREQUAL Name2)
	message("${Name1} is equal to ${Name2}")
endif()

set(Name1 Charlie)
set(Name2 Charlies)

if(Name1 STRLESS Name2)
	message("${Name1} is less than ${Name2}")
elseif(Name1 STRGREATER Name2)
	message("${Name1} is greater than ${Name2}")
elseif(Name1 STREQUAL Name2)
	message("${Name1} is equal to ${Name2}")
endif()

set(Name1 Charlie)
set(Name2 Charlie)

if(Name1 STRLESS Name2)
	message("${Name1} is less than ${Name2}")
elseif(Name1 STRGREATER Name2)
	message("${Name1} is greater than ${Name2}")
elseif(Name1 STREQUAL Name2)
	message("${Name1} is equal to ${Name2}")
endif()

message("=====while loop=======")

set(VAR a)
while(NOT VAR STREQUAL "aaaaaaaaaa")
	set(VAR ${VAR}a)
	message(${VAR})
endwhile()

message("=====foreach loops=======")
foreach(Name Alice Bob Charlie)
	message(${Name})
endforeach()

foreach(x RANGE 100 105)
	message("Person ${x}")
endforeach()

set(VAR1 0;1)
set(VAR2 2 3)
set(VAR3 "4 5")

foreach(x IN LISTS VAR1 VAR2 VAR3)
	message("x = ${x}")
endforeach()

message("=====functions=======")
function(print_detail)
	message("My name is Bob")
endfunction()

print_detail()

function(print_detail1 var)
	message("My name is ${var}")
endfunction()

function(print_detail)
	message("1.My name is Bob")
endfunction()

set(Name Charlie)

print_detail1(${Name})
print_detail()
_print_detail()


function (g name_var)
	message("My name is ${${name_var}}")
	if (DEFINED ARGV1)
		message("Here the argv1: ${ARGV1}")
	endif()

	message("ARGC= ${ARGC}")
	message("ARGV= ${ARGV}")
	message("ARGN= ${ARGN}")

	if (DEFINED ARGV0)
		message("Here the argv0: ${ARGV0}")
	endif()

	if (DEFINED ARGV2)
		message("Here the argv2: ${ARGV2}")
	endif()

	if (DEFINED ARGV3)
		message("Here the argv3: ${ARGV3}")
	endif()


endfunction()

set(Name Charlie)
g(Name Bob)
g(Name)
g(Name Bob Alice)

message("=====scope functions=======")
set(Name Charlie)

function(myFunction)
	message("Inside the function: Before modification: ${Name}")
	set(Name Bob)
	message("Inside the function: After modification: ${Name}")
endfunction()

message("Outside the function: before: ${Name}")
myFunction()
message("Outside the function: after: ${Name}")

message("=====scope functions part 2=======")

set(Name Charlie)
function(myFunction1)
	message("Inside the function: Before modification: ${Name}")
	set(Name Bob PARENT_SCOPE)
	message("Inside the function: After modification: ${Name}")
endfunction()

message("Outside the function: before: ${Name}")
myFunction1()
message("Outside the function: after: ${Name}")

message("=====macros=======")
macro(myFunction2 name_var)
	message("Inside the macro: Before modification: ${name_var}")
	set(name_var abc)
	message("Inside the macro: After modification: ${name_var}")
endmacro()

myFunction2(Charlie)
