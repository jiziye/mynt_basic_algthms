//
// Created by cg on 9/17/19.
//
#include <gtest/gtest.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "kinematics/quarternion.h"
#include "math_utils.hpp"

TEST(kinematics, quarternion)
{
    // mynt::Quarternion q(); // TODO: why
    mynt::Quarternion qa;
    mynt::Quarternion qb(0.93, 0.2, 0.5, 0.1);
    mynt::Quarternion qc = mynt::Quarternion::unit_random();

    std::cout << "qa: " << qa << std::endl;
    std::cout << "qb: " << qb << std::endl;
    std::cout << "qc: " << qc << std::endl;

    mynt::Matrix m_qb = qb.rotation_matrix();
    std::cout << "m_qb_01:\n" << m_qb << std::endl;

    Eigen::Vector4d v4(0.2, 0.5, 0.1, 0.93);
    Eigen::Matrix3d m3 = msckf::quaternionToRotation(v4);
    std::cout << "m_qb_02:\n" << m3 << std::endl;
}
