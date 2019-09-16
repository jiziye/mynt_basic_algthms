//
// Created by cg on 9/16/19.
//

#include <gtest/gtest.h>

#include "cv/types.h"

TEST(cv, Size)
{
    mynt::Size sz = mynt::Size();
    std::cout << "sz: " << sz << std::endl;

    mynt::Size sza = mynt::Size(100,200);
    mynt::Size szb = mynt::Size(200,300);
    mynt::Size szc = sza + szb;
    std::cout << "szc: " << szc << ", area: " << szc.area() << std::endl;
}
