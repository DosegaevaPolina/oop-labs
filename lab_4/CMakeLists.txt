cmake_minimum_required(VERSION 3.12)
project(FiguresTemplates CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(sanitizers INTERFACE)
target_compile_options(sanitizers INTERFACE -fsanitize=address,undefined,integer)
target_link_options(sanitizers INTERFACE -fsanitize=address,undefined,integer)

add_executable(figures_templates_main main.cpp)
target_link_libraries(figures_templates_main sanitizers)

enable_testing()

add_executable(figures_templates_tests figures_tests.cpp)
target_link_libraries(figures_templates_tests GTest::gtest_main sanitizers)

include(GoogleTest)
gtest_discover_tests(figures_templates_tests)

