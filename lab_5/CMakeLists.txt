cmake_minimum_required(VERSION 3.12)
project(Allocator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(allocator_main main.cpp)
target_link_libraries(allocator_main sanitizers)

enable_testing()

fuzztest_setup_fuzzing_flags()
add_executable(allocator_tests allocator_tests.cpp)
link_fuzztest(allocator_tests)

include(GoogleTest)
gtest_discover_tests(allocator_tests)

