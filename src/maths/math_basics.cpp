//
// Created by cg on 9/21/19.
//

#include "maths/math_basics.h"

#include <cmath>
#include <random>

namespace mynt {

    unsigned long int g_state;

    int uniform_integer(int min, int max) {
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }

    void rng_mwc_init(unsigned long int state) { g_state = state; }

    unsigned int rng_mwc_next() {
        g_state = (unsigned long int)(unsigned)g_state* /*CV_RNG_COEFF*/ 4164903690U + (unsigned)(g_state >> 32);
        return (unsigned)g_state;
    }
}
