include_directories(${PROJECT_SOURCE_DIR}/include)

set(CMAKE_MODULE_PATH APPEND "${CMAKE_SOURCE_DIR}/cmake_modules/")
find_package(Eigen3)
if(Eigen3_FOUND)
    include_directories(${EIGEN3_INCLUDE_DIR})
endif()

link_libraries(gtest pthread)

## maths
add_executable(test_maths gtest_main.cpp test_math.cpp)
target_link_libraries(test_maths mynt_maths)

## computer vision
find_package(OpenCV REQUIRED COMPONENTS core highgui imgproc features2d calib3d video)
if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
endif()
add_executable(test_cv gtest_main.cpp test_cv.cpp)
target_link_libraries(test_cv mynt_cv ${OpenCV_LIBS})

## kinematics
add_executable(test_kinematics gtest_main.cpp test_kinematics.cpp)
target_link_libraries(test_kinematics mynt_kinematics ${OpenCV_LIBS})
