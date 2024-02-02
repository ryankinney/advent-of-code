cmake_minimum_required(VERSION 3.22.1)

project(Day3)
set(CMAKE_BUILD_TYPE Debug)

add_executable(unit-tests Engine.cpp UnitTests.cpp)
target_link_libraries(unit-tests gtest gtest_main)