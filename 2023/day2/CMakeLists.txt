cmake_minimum_required(VERSION 3.22.1)

project(Day2)
set(CMAKE_BUILD_TYPE Debug)

add_executable(unit-tests parse.cpp process.cpp unit-tests.cpp)
target_link_libraries(unit-tests gtest gtest_main)