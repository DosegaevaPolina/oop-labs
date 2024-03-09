cmake_minimum_required(VERSION 3.12)
project(NPCs CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(npcs OBJECT npc.cpp editor.cpp)
target_link_libraries(npcs sanitizers)

add_executable(npcs_main main.cpp)
target_link_libraries(npcs_main npcs)

