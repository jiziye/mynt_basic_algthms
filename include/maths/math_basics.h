//
// Created by cg on 9/17/19.
//

#ifndef MYNT_BASIC_ALGTHMS_MATH_BASICS_H
#define MYNT_BASIC_ALGTHMS_MATH_BASICS_H

#include <cmath>
#include <random>

namespace mynt {

    inline int uniform_integer(int min, int max) {
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }
}

#endif //MYNT_BASIC_ALGTHMS_MATH_BASICS_H
