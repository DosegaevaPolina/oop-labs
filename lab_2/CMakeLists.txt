cmake_minimum_required(VERSION 3.12)
project(Five CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(five main.cpp five.cpp)
target_compile_options(five PRIVATE -fsanitize=address,undefined,integer)
target_link_options(five PRIVATE -fsanitize=address,undefined,integer)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/v1.14.x.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

#add_executable(tests five_tests.cpp five.cpp)
#target_link_libraries(tests GTest::gtest_main)
#gtest_discover_tests(tests)

