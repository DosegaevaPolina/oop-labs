cmake_minimum_required(VERSION 3.12)
project(Editor CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(editor OBJECT npc.cpp editor.cpp)
target_include_directories(editor
  PUBLIC
  "$<TARGET_PROPERTY:GTest::gtest,INTERFACE_INCLUDE_DIRECTORIES>")
target_link_libraries(editor sanitizers)

add_executable(editor_main main.cpp)
target_link_libraries(editor_main editor)

enable_testing()

add_executable(editor_tests tests.cpp)
target_link_libraries(editor_tests editor GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(editor_tests)

