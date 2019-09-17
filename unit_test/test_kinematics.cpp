//
// Created by cg on 9/17/19.
//
#include <gtest/gtest.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "kinematics/quarternion.h"

TEST(kinematics, quarternion)
{
    mynt::Quarternion qa;
    mynt::Quarternion qb(0.93, 0.2, 0.5, 0.1);
    mynt::Quarternion qc = mynt::Quarternion::unit_random();

    std::cout << "qa: " << qa << std::endl;
    std::cout << "qb: " << qb.normalized() << std::endl;
    std::cout << "qc: " << qc << std::endl;
}
