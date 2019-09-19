//
// Created by cg on 9/16/19.
//

#include <gtest/gtest.h>

#include "maths/math_basics.h"
#include "maths/random_numbers.h"
#include "maths/matrix.h"
#include "maths/vector.h"

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

