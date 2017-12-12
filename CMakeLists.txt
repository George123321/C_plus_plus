cmake_minimum_required(VERSION 3.0)

################################
# GTest
################################
ADD_SUBDIRECTORY (googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_subdirectory(Lab13)
add_subdirectory(contest9)
add_subdirectory(ready_to_test)