include_directories(${PROJECT_SOURCE_DIR}/include)

link_libraries(gtest pthread)

## maths
add_executable(test_maths gtest_main.cpp test_math.cpp)
target_link_libraries(test_maths mynt_maths)

## computer vision
add_executable(test_cv gtest_main.cpp test_cv.cpp)

## kinematics
