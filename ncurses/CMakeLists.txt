# libraries
add_library(user-input user-input.c)

# executables
add_executable(cdocs main.c)

# linking
target_link_libraries(cdocs user-input)
target_link_libraries(cdocs ncurses)
target_link_libraries(cdocs net)
target_link_libraries(cdocs ot-client)
