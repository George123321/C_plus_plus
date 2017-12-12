cmake_minimum_required(VERSION 3.8)
project(Final_Test)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp class.h)
add_executable(Final_Test ${SOURCE_FILES})

project(tests)
add_executable(final_test-tests Final_Test-tests.cpp)
#add_library(123 vector.h)
target_link_libraries(final_test-tests gtest gtest_main)