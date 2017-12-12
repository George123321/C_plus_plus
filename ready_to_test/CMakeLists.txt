cmake_minimum_required(VERSION 3.8)
project(ready_to_test)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp vector.h)
#set(SOURCE_FILES main.cpp ready_to_test-tests.cpp vector.h)
add_executable(ready_to_test ${SOURCE_FILES})

project(tests)
add_executable(ready_to_test-tests ready_to_test-tests.cpp)
#add_library(123 vector.h)
target_link_libraries(ready_to_test-tests gtest gtest_main)