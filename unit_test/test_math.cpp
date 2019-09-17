//
// Created by cg on 9/16/19.
//

#include <gtest/gtest.h>

#include "maths/matrix.h"

TEST(maths, Matrix)
{
    mynt::Matrix ma = mynt::Matrix::eye(5);
    std::cout << "ma: \n" << ma << std::endl;
}

