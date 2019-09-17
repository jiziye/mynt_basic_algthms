cmake_minimum_required(VERSION 3.1)
project(mynt_basic_algthms)

option(BUILD_TEST "Build Unit Test Program for the project (requires GTest)" OFF)

set(CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if(CMAKE_BUILD_TYPE MATCHES "Release")
    set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -std=c++11 -O3")
else(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -std=c++11 -O0 -g -Wall")
    add_definitions(-D__USER_DEBUG__)
endif(CMAKE_BUILD_TYPE MATCHES "Release")

include_directories(include)

## maths
add_library(mynt_maths SHARED src/maths/matrix.cpp)

## computer vision

## kinematics

## unit test
if(BUILD_TEST)
    enable_testing()
    find_package(GTest)
    if(GTest_FOUND)
        include_directories(${GTEST_INCLUDE_DIRS})
        add_subdirectory(unit_test)
    endif()
endif()
