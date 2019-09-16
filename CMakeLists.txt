cmake_minimum_required(VERSION 3.1)
project(mynt_basic_algthms)

option(UnitTest "Unit Test with GTest" false)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

## maths
add_library(mynt_maths SHARED src/maths/matrix.cpp)

## computer vision

## kinematics

## unit test
if(UnitTest)
    enable_testing()
    find_package(GTest)
    if(GTest_FOUND)
        include_directories(${GTEST_INCLUDE_DIRS})
        add_subdirectory(unit_test)
    endif()
endif()
