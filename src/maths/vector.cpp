//
// Created by cg on 9/24/19.
//

#include "maths/vector.h"

namespace mynt {

    /**
     * @brief Create a skew-symmetric matrix from a 3-element vector.
     * @param w
     * @note Performs the operation:
     *  w   ->  [  0 -w3  w2]
     *          [ w3   0 -w1]
     *          [-w2  w1   0]
     * @return
     */
    Matrix skew_symmetric(const Vector<3> &w) {
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

    /**
     * @brief s * M
     * @param s
     * @param M
     * @return
     */
    Matrix operator*(FLOAT s, Matrix M) { return M * s; }
}