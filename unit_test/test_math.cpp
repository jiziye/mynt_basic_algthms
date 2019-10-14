//
// Created by cg on 9/16/19.
//

#include <gtest/gtest.h>

#include <Eigen/Core>

#include "maths/math_basics.h"
#include "maths/vector.h"
#include "maths/random_numbers.h"

TEST(maths, random_number)
{
    random_numbers::RandomNumberGenerator random_gen;
    int rng01 = random_gen.uniformInteger(0, 100);

    int rng02 = mynt::uniform_integer(0, 100);

    std::cout << "rng01: " << rng01 << std::endl;
    std::cout << "rng02: " << rng02 << std::endl;
}

TEST(maths, Matrix)
{
    mynt::Matrix m3 = 3.5 * mynt::Matrix::eye(3);
    m3(0, 2) = 1.1;
    m3(2, 0) = 2.2;
    mynt::Matrix ma = 2.3 * mynt::Matrix::eye(5);
    ma.set_mat(0, 2, m3);
    std::cout << "ma: \n" << ma << std::endl;
    ma.conservative_resize(7,4);
    std::cout << "ma conservative_resize: \n" << ma << std::endl;

    Eigen::Vector2d v21(1,1);
    Eigen::Vector2d v22(2,2);
    Eigen::Matrix2d m01;
    m01 << v21, v22;
    std::cout << "m01:\n" << m01 << std::endl;

    mynt::Vector2 v1({1,1});
    mynt::Vector2 v2({2,2});
    mynt::Matrix m02 = mynt::vec2mat(v1, v2);
    std::cout << "m02:\n" << m02 << std::endl;

    Eigen::MatrixXd mx01(4,4);
    mx01 <<
        1, 2, 3, 4,
        5, 6, 7, 8,
        0, 1, 2, 3,
        6, 7, 8, 9;
    mx01.conservativeResize(3,3);
    std::cout << "mx01:\n" << mx01 << std::endl;

    Eigen::MatrixXd mx02 = Eigen::MatrixXd::Identity(3, 5);
    std::cout << "mx02:\n" << mx02 << std::endl;

    std::cout << "mx03:\n" << mynt::Matrix::identity(5, 3) << std::endl;
}

TEST(maths, Vector)
{
    Eigen::VectorXd vX(5);
    vX << 1,2,3,4,5;
    vX.conservativeResize(3);
    std::cout << "vX conservativeResize:" << vX.transpose() << std::endl;

    mynt::VectorX vX01(5);
    vX01[0] = 1;
    vX01[1] = 2;
    vX01[2] = 3;
    vX01[3] = 4;
    vX01[4] = 5;
    vX01.conservative_resize(3);
    std::cout << "vX01 conservativeResize:" << vX01.transpose() << std::endl;

    Eigen::Vector4d v4(1,2,3,4);
    std::cout << "va sqnorm 01: " << v4.squaredNorm() << std::endl;
    std::cout << "va l1norm 01: " << v4.lpNorm<1>() << std::endl;

    mynt::FLOAT val[] = {1,2,3,4};
    mynt::Vector5 va = mynt::Vector5(val);

    std::cout << "va sqnorm 02: " << va.squared_l2norm() << std::endl;
    std::cout << "va l1norm 02: " << va.l1norm() << std::endl;

    std::cout << "va t * va" << va.transpose() * va << std::endl;

    va *= 2;

    va[1] = 10;

    mynt::Vector5 vb = va/2.0;
    vb += va;
    mynt::Vector5 vc = va + vb;

    mynt::Vector3 vd = va.block<3>(1);

    mynt::Vector<9> ve({1,2,3,4,5});

    std::cout << "va: " << va.transpose() << std::endl;
    std::cout << "vb: " << vb.transpose() << std::endl;
    std::cout << "vc: " << vc.transpose() << std::endl;
    std::cout << "vd: " << vd.transpose() << std::endl;
    std::cout << "ve: " << ve.transpose() << std::endl;

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

