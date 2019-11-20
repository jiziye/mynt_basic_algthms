//
// Created by cg on 9/16/19.
//

#include <chrono>

#include <gtest/gtest.h>

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/SVD>
#include <Eigen/Cholesky>

#include <opencv2/core/core.hpp>

#include "maths/math_basics.h"
#include "maths/vector.h"
#include "maths/random_numbers.h"

#include "maths/svd_fulluv.h"

TEST(maths, random_number)
{
    random_numbers::RandomNumberGenerator random_gen;
    int rng01 = random_gen.uniformInteger(0, 100);

    int rng02 = mynt::uniform_integer(0, 100);

    std::cout << "rng01: " << rng01 << std::endl;
    std::cout << "rng02: " << rng02 << std::endl;

    std::mt19937 rng_stdmt(0x12345678);
    std::cout << "rng03: " << rng_stdmt() << std::endl;

    cv::RNG_MT19937 rng_cvmt(0x12345678);
    std::cout << "rng04: " << rng_cvmt.next() << std::endl;

    cv::RNG rng(0x12345678);
    std::cout << "rng05: " << rng.next() << std::endl;

    mynt::rng_mwc_init(0x12345678);
    std::cout << "rng06: " << mynt::rng_mwc_next() << std::endl;
}

TEST(maths, Matrix)
{
    std::cout << "init matrix: \n" << mynt::Matrix(3,3) << std::endl;

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

    mynt::VectorX vX01(5);
    vX01[0] = 1;
    vX01[1] = 2;
    vX01[2] = 3;
    vX01[3] = 4;
    vX01[4] = 5;
    mynt::VectorX vX02 = vX01 * 2;
    mynt::Matrix mX02 = mynt::vec2mat(vX01, vX02);
    std::cout << "mX02:\n" << mX02 << std::endl;

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

TEST(math, SVD)
{
    Eigen::MatrixXd emx;
    emx.setRandom(11, 9);

    /// Eigen
    Eigen::JacobiSVD<Eigen::MatrixXd> svd_helper(emx, Eigen::ComputeFullU | Eigen::ComputeFullV);
    std::cout << "=============== Eigen ================" << std::endl;
    std::cout << "SVD U (Eigen): \n" << svd_helper.matrixU() << std::endl;
    std::cout << "SVD V (Eigen): \n" << svd_helper.matrixV() << std::endl;
    std::cout << "SVD S (Eigen): \n" << svd_helper.singularValues() << std::endl;

    /// OpenCV
    cv::Mat cvH(emx.rows(), emx.cols(), CV_32F);
    for(int i=0; i<emx.rows(); ++i)
        for(int j=0; j<emx.cols(); ++j)
            cvH.at<float>(i, j) = emx(i, j);
    cv::Mat cvS, cvU, cvVt;
    auto start_time = std::chrono::steady_clock::now();
    cv::SVD::compute(cvH, cvS, cvU, cvVt, cv::SVD::FULL_UV); // cv::SVD::FULL_UV
    auto end_time = std::chrono::steady_clock::now();
    std::cout << "time OpenCV SVD solve: " << std::chrono::duration<double>(end_time-start_time).count()*1000 << " ms" << std::endl;
    std::cout << "=============== OpenCV ================" << std::endl;
    std::cout << "SVD U (OpenCV): \n" << cvU << std::endl;
    std::cout << "SVD V (OpenCV): \n" << cvVt.t() << std::endl;
    std::cout << "SVD S (OpenCV): \n" << cvS << std::endl;

    /// mynt
//    mynt::Matrix A(emx.rows(), emx.cols());
//    for(int i=0; i<emx.rows(); ++i)
//        for(int j=0; j<emx.cols(); ++j)
//            A(i, j) = emx(i, j);
//    mynt::Matrix U, W, V;
//    A.svd(U, W, V);
//    std::cout << "=============== Viso2 ================" << std::endl;
//    std::cout << "SVD U (Viso2):\n" << U << std::endl;
//    std::cout << "SVD V (Viso2):\n" << V << std::endl;
//    std::cout << "SVD W (Viso2):\n" << W << std::endl;

    /// Shen
    mynt::Matrix In(emx.rows(), emx.cols()), U1, W1, Vt1;
    for (int i = 0; i < emx.rows(); i++) {
        for (int j = 0; j < emx.cols(); j++) {
            In(i, j) = emx(i, j);
        }
    }
    start_time = std::chrono::steady_clock::now();
    mynt::svd_fulluv(In, W1, U1, Vt1);
    end_time = std::chrono::steady_clock::now();
    std::cout << "time Shen SVD solve: " << std::chrono::duration<double>(end_time-start_time).count()*1000 << " ms" << std::endl;
    std::cout << "=============== Shen ================" << std::endl;
    std::cout << "SVD U (Shen):\n" << U1 << std::endl;
    std::cout << "SVD V (Shen):\n" << Vt1.transpose() << std::endl;
    std::cout << "SVD W (Shen):\n" << W1 << std::endl;
}

TEST(math, ldlt) {
    Eigen::MatrixXd emx;
    emx.setRandom(3, 3);

//    Eigen::MatrixXd emx(3,4);
//    emx << 1,2,3,4, 4,5,6,7, 7,8,9,10;

    emx = emx * emx.transpose();

    Eigen::VectorXd b1 = Eigen::VectorXd::Random(3);

    std::cout << "LDLT L (Eigen): \n" << emx.ldlt().matrixL().toDenseMatrix() << std::endl;
    std::cout << "LDLT D (Eigen): \n" << emx.ldlt().vectorD() << std::endl;

    auto start_time = std::chrono::steady_clock::now();
    Eigen::VectorXd x1 = emx.ldlt().solve(b1);
    auto end_time = std::chrono::steady_clock::now();
    std::cout << "time Eigen ldlt solve: " << std::chrono::duration<double>(end_time-start_time).count()*1000 << " ms" << std::endl;
    std::cout << "LDLT (Eigen): \n" << x1 << std::endl;

    mynt::Matrix A(emx.rows(), emx.cols());
    for(int i=0; i<emx.rows(); ++i)
        for(int j=0; j<emx.cols(); ++j)
            A(i, j) = emx(i, j);

    mynt::Matrix L, D;
    mynt::Vector3 b;
    b[0] = b1[0];
    b[1] = b1[1];
    b[2] = b1[2];
    A.ldlt(L, D);
    std::cout << "LDLT L:\n" << L << std::endl;
    std::cout << "LDLT D:\n" << D << std::endl;

    start_time = std::chrono::steady_clock::now();
    mynt::Vector3 x = mynt::solve_ldlt(A, b);
    end_time = std::chrono::steady_clock::now();
    std::cout << "time mynt ldlt solve: " << std::chrono::duration<double>(end_time-start_time).count()*1000 << " ms" << std::endl;
    std::cout << "LDLT:\n" << x << std::endl;
}
