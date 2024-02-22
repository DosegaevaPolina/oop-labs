cmake_minimum_required(VERSION 3.12)
project(Five CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(code-coverage)

add_library(five OBJECT five.cpp)
target_compile_options(five PUBLIC -fsanitize=address,undefined,integer)
target_link_options(five PUBLIC -fsanitize=address,undefined,integer)
target_code_coverage(five)

add_executable(five_main main.cpp)
target_link_libraries(five_main five)
target_code_coverage(five_main)

enable_testing()

add_executable(tests five_tests.cpp)
target_link_libraries(tests five GTest::gtest_main)
target_code_coverage(tests COVERAGE_TARGET_NAME five EXCLUDE five_tests.cpp)

include(GoogleTest)
gtest_discover_tests(tests)
