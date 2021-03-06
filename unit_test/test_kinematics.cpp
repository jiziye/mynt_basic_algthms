//
// Created by cg on 9/17/19.
//
#include <gtest/gtest.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "kinematics/rotation_matrix.h"
#include "math_utils.hpp"

TEST(kinematics, Quarternion)
{
    // mynt::Quarternion q(); // TODO: why
    mynt::Quarternion qa;
    mynt::Quarternion qb(0.93, 0.2, 0.5, 0.1);
    mynt::Quarternion qc = mynt::Quarternion::unit_random();

    std::cout << "qa: " << qa << std::endl;
    std::cout << "qb: " << qb << std::endl;
    std::cout << "qc: " << qc << endll;

    // rotation_matrix
    mynt::Matrix m_qb = qb.rotation_matrix();
    std::cout << "m_qb_01:\n" << m_qb << std::endl;

    Eigen::Vector4d v4b(qb.x(), qb.y(), qb.z(), qb.w());
    Eigen::Matrix3d mb = msckf::quaternionToRotation(v4b);
    std::cout << "m_qb_02:\n" << mb << endll;

    // normalized
    std::cout << "qb  normalized: " << qb.normalized() << std::endl;
    msckf::quaternionNormalize(v4b);
    std::cout << "v4b normalized: " << v4b.transpose() << endll;

    // q1 * q2
    Eigen::Vector4d v4c(qc.x(), qc.y(), qc.z(), qc.w());

    mynt::Quarternion q = qb * qc;
    std::cout << "qb * qc 01: " << q << std::endl;

    Eigen::Vector4d v4 = msckf::quaternionMultiplication(v4b, v4c);
    std::cout << "qb * qc 02: " << v4.transpose() << endll;

    // small_angle_quaternion
    mynt::Vector<3> v3_s = qc.vec();
    q = mynt::Quarternion::small_angle_quaternion(v3_s);
    std::cout << "small q 01: " << q << std::endl;

    Eigen::Vector3d v3_e;
    v3_e[0] = v3_s[0];
    v3_e[1] = v3_s[1];
    v3_e[2] = v3_s[2];
    v4 = msckf::smallAngleQuaternion(v3_e);
    std::cout << "small q 02: " << v4.transpose() << endll;
}

TEST(kinematics, RotationMatrix)
{
    // rotationToQuaternion
    mynt::Quarternion qa = mynt::Quarternion::unit_random();
    mynt::RotationMatrix m_qa = qa.rotation_matrix();

    std::cout << "m_qa:\n" << m_qa << std::endl;

    mynt::Quarternion q01 = m_qa.quarternion();
    std::cout << "q01: " << q01 << std::endl;

    Eigen::Matrix3d m3;
    for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
            m3(i,j) = m_qa(i,j);
    Eigen::Vector4d q02 = msckf::rotationToQuaternion(m3);
    std::cout << "q02: " << q02.transpose() << endll;
}
