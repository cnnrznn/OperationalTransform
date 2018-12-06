cmake_minimum_required (VERSION 2.6)
project (CDocs)

include_directories(${PROJECT_SOURCE_DIR}/net)

add_subdirectory(${PROJECT_SOURCE_DIR}/core)
add_subdirectory(${PROJECT_SOURCE_DIR}/ncurses)
add_subdirectory(${PROJECT_SOURCE_DIR}/net)
