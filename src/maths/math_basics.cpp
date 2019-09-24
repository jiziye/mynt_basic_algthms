//
// Created by cg on 9/21/19.
//

#include "maths/math_basics.h"

#include <cmath>
#include <random>

namespace mynt {

    int uniform_integer(int min, int max) {
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }
}
