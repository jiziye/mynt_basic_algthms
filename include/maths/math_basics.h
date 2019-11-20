//
// Created by cg on 9/17/19.
//

#ifndef MYNT_BASIC_ALGTHMS_MATH_BASICS_H
#define MYNT_BASIC_ALGTHMS_MATH_BASICS_H

namespace mynt {

    int uniform_integer(int min, int max);

    /// from cv::RNG wihich uses Multiply-With-Carry algorithm
    void rng_mwc_init(unsigned long int state);
    unsigned int rng_mwc_next();
}

#endif //MYNT_BASIC_ALGTHMS_MATH_BASICS_H
