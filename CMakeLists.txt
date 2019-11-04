cmake_minimum_required(VERSION 3.1)
project(mynt_basic_algthms)

option(BUILD_TEST "Build Unit Test Program for the project (requires GTest)" OFF)
option(BUILD_DOC  "Create and install the HTML based API documentation (requires Doxygen)" OFF)

set(CMAKE_CXX_STANDARD 11) # -std=gnu++11

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if(CMAKE_BUILD_TYPE MATCHES "Release")
    set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O3") # -std=c++11
else(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O0 -g -Wall")
    add_definitions(-D__USER_DEBUG__)
endif(CMAKE_BUILD_TYPE MATCHES "Release")

include_directories(include)

add_subdirectory(3rdparty/fast)
include_directories(3rdparty/fast/include)

## maths
find_package(Boost REQUIRED COMPONENTS system)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    link_directories(${Boost_LIBRARY_DIR})
endif()
add_library(mynt_maths SHARED src/maths/math_basics.cpp src/maths/matrix.cpp src/maths/vector.cpp src/maths/random_numbers.cpp)
target_link_libraries(mynt_maths ${Boost_LIBRARIES})

## kinematics
add_library(mynt_kinematics SHARED src/kinematics/rotation_matrix.cpp src/kinematics/quarternion.cpp src/kinematics/convertor.cpp)
target_link_libraries(mynt_kinematics mynt_maths)

## computer vision
include_directories("/usr/include/eigen3/")
add_library(mynt_cv SHARED
        src/cv/types.cpp src/cv/undistort.cpp src/cv/calib3d.cpp src/cv/corner_detector.cpp src/cv/visual_tracking.cpp src/cv/image_filtering.cpp)
target_link_libraries(mynt_cv mynt_kinematics fast)

## unit test
if(BUILD_TEST)
    enable_testing()
    find_package(GTest)
    if(GTest_FOUND)
        include_directories(${GTEST_INCLUDE_DIRS})
        add_subdirectory(unit_test)
    endif()
endif()

## build doc with doxygen
if(BUILD_DOC)
    find_package(Doxygen)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "NOT Found doxygen which is needed to build the documentation.")
    else()
        message(STATUS "Found doxygen, run `make doc` to build documentation")
        set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/config/Doxyfile.config)
        set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
        configure_file(${doxyfile_in} ${doxyfile} @ONLY)
        add_custom_target(doc
                COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Generating API documentation with Doxygen"
                VERBATIM)
        install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
    endif()
endif()

INSTALL(TARGETS mynt_maths mynt_kinematics
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(DIRECTORY include/maths include/cv include/kinematics
        DESTINATION include)
install(FILES include/common.h DESTINATION include)