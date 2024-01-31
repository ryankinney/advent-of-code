cmake_minimum_required(VERSION 3.22.1)

project(day1)
set(CMAKE_BUILD_TYPE Debug)

add_executable(unit-tests part1.cpp part2.cpp unit-tests.cpp)
target_link_libraries(unit-tests gtest gtest_main)