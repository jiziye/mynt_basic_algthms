//
// Created by cg on 9/16/19.
//

#include <gtest/gtest.h>

#include "maths/math_basics.h"
#include "maths/random_numbers.h"

TEST(maths, random_number) {
    random_numbers::RandomNumberGenerator random_gen;
    int rng01 = random_gen.uniformInteger(0, 100);

    int rng02 = mynt::uniform_integer(0, 100);

    std::cout << "rng01: " << rng01 << std::endl;
    std::cout << "rng02: " << rng02 << std::endl;
}

TEST(maths, Matrix)
{
    mynt::Matrix ma = mynt::Matrix::eye(5);
    std::cout << "ma: \n" << 3.5 * ma << std::endl;
}

TEST(maths, Vector)
{
    mynt::FLOAT val[] = {1,2,3,4,5};
    mynt::Vector5 va = mynt::Vector5(val);

    va[1] = 10;

    mynt::Vector5 vb = va/2.0;
    mynt::Vector5 vc = va + vb;

    mynt::Vector3 vd = va.block<3>(1);

    std::cout << "va: " << va.transpose() << std::endl;
    std::cout << "vb: " << vb.transpose() << std::endl;
    std::cout << "vc: " << vc.transpose() << std::endl;
    std::cout << "vd: " << vd.transpose() << std::endl;

    std::cout << "va dot va: " << va.dot(va) << std::endl;

    mynt::Matrix ma =  va * va.transpose();
    std::cout << "ma: \n" << ma << std::endl;
}

TEST(maths, math_basic)
{
    mynt::FLOAT val[] = {1,2,3};
    mynt::Vector3 va(val);
    mynt::Matrix ma = mynt::skew_symmetric(va);
    std::cout << "skew_symmetric ma: \n" << ma << std::endl;
}

