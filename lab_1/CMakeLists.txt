cmake_minimum_required(VERSION 3.12)
project(devowel CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Devowel main.cpp devowel.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/v1.14.x.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(devowel_test devowel_test.cpp devowel.cpp)
target_link_libraries(devowel_test GTest::gtest_main)
gtest_discover_tests(devowel_test)

