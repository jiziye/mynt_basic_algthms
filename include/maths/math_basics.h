//
// Created by cg on 9/17/19.
//

#ifndef MYNT_BASIC_ALGTHMS_MATH_BASICS_H
#define MYNT_BASIC_ALGTHMS_MATH_BASICS_H

#include <cmath>
#include <random>

#include "maths/vector.h"

namespace mynt {

    inline int uniform_integer(int min, int max) {
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }

    inline Matrix skew_symmetric(const Vector &w) {
        Matrix w_hat(3, 3);
        w_hat(0, 0) =  0;
        w_hat(0, 1) = -w[2];
        w_hat(0, 2) =  w[1];
        w_hat(1, 0) =  w[2];
        w_hat(1, 1) =  0;
        w_hat(1, 2) = -w[0];
        w_hat(2, 0) = -w[1];
        w_hat(2, 1) =  w[0];
        w_hat(2, 2) =  0;
        return w_hat;
    }
}

#endif //MYNT_BASIC_ALGTHMS_MATH_BASICS_H
