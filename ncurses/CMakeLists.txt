cmake_minimum_required (VERSION 2.6)
project (CDocs)

# libraries
add_library(user-input user-input.c)

# executables
add_executable(cdocs main.c)

# linking
target_link_libraries(cdocs user-input)
target_link_libraries(cdocs ncurses)
