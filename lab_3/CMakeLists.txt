cmake_minimum_required(VERSION 3.12)
project(Figures CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(figures OBJECT figure.cpp pentagon.cpp hexagon.cpp octagon.cpp array.cpp)
target_compile_options(figures PUBLIC -fsanitize=address,undefined,integer)
target_link_options(figures PUBLIC -fsanitize=address,undefined,integer)

add_executable(figures_main main.cpp)
target_link_libraries(figures_main figures)

enable_testing()

add_executable(figures_tests figures_tests.cpp)
target_link_libraries(figures_tests figures GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(figures_tests)

