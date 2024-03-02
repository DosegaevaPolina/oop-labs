cmake_minimum_required(VERSION 3.12)
project(Labs CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(googletest)
add_subdirectory(lab_2)
add_subdirectory(lab_3)
add_subdirectory(lab_4)
