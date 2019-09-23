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
    Matrix skew_symmetric(const Vector<3> &w);

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
    template<unsigned int _M>
    Vector<_M> operator*(FLOAT s, Vector<_M> V)  { return V * s; }

    /**
     * @brief M * V
     * @param M
     * @param V
     * @return
     */
    template<unsigned int _M, unsigned int _N>
    static Vector<_M> operator*(const Matrix &M, const Vector<_N> &V) {
        assert(M.n == V.size() && M.m == _M);
        Vector<_M> v;
        for(int i=0; i<M.m; ++i) {
            FLOAT sum_i = 0.0;
            for(int j=0; j<M.n; ++j)
                sum_i += M(i,j) * V[j];
            v[i] = sum_i;
        }
        return v;
    }
}

#endif //MYNT_BASIC_ALGTHMS_MATH_BASICS_H
