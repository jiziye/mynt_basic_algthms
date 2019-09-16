//
// Created by cg on 9/16/19.
//

#include <gtest/gtest.h>

#include "maths/matrix.h"

TEST(maths, Matrix)
{
    Matrix ma = Matrix::eye(5);
    std::cout << "ma: \n" << ma << std::endl;
}

