//
// Created by cg on 9/17/19.
//

#ifndef MYNT_BASIC_ALGTHMS_MATH_BASICS_H
#define MYNT_BASIC_ALGTHMS_MATH_BASICS_H

#include "maths/vector.h"

namespace mynt {

    int uniform_integer(int min, int max);

    /**
     * @brief Create a skew-symmetric matrix from a 3-element vector.
     * @param w
     * @note Performs the operation:
     *  w   ->  [  0 -w3  w2]
     *          [ w3   0 -w1]
     *          [-w2  w1   0]
     * @return
     */
    Matrix skew_symmetric(const Vector &w);

    /**
     * @brief s * M
     * @param s
     * @param M
     * @return
     */
    Matrix operator*(FLOAT s, Matrix M);

    /**
     * @brief s * V
     * @param s
     * @param V
     * @return
     */
    Vector operator*(FLOAT s, Vector V);

    /**
     * @brief M * V
     * @param M
     * @param V
     * @return
     */
    Vector operator*(const Matrix &M, const Vector &V);
}

#endif //MYNT_BASIC_ALGTHMS_MATH_BASICS_H
