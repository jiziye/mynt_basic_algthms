//
// Created by cg on 9/16/19.
//

#include <gtest/gtest.h>

#include "maths/matrix.h"
#include "maths/vector.h"

TEST(maths, Matrix)
{
    mynt::Matrix ma = mynt::Matrix::eye(5);
    std::cout << "ma: \n" << ma << std::endl;
}

TEST(maths, Vector)
{
    mynt::FLOAT val[] = {1,2,3,4,5};
    mynt::Vector va = mynt::Vector(5, val);

    va[1] = 9.6;

    mynt::Vector vb = va/2.0;
    mynt::Vector vc = va + vb;

    std::cout << "va: " << va << std::endl;
    std::cout << "vb: " << vb << std::endl;
    std::cout << "vc: " << vc << std::endl;
}

