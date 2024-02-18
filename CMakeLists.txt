cmake_minimum_required(VERSION 3.12)
project(Labs CXX)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(googletest)
add_subdirectory(lab_2)
