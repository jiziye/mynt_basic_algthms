//
// Created by cg on 9/20/19.
//

#include "kinematics/quarternion.h"

namespace mynt {

    Quarternion::Quarternion() {
        v4_ = Vector(4);
#if Q_HAMILTON
        v4_[0] = 1.0;
        v4_[1] = 0.0;
        v4_[2] = 0.0;
        v4_[3] = 0.0;
#else
        v4_[0] = 0.0;
        v4_[1] = 0.0;
        v4_[2] = 0.0;
        v4_[3] = 1.0;
#endif
    }

    Quarternion::Quarternion(FLOAT w, FLOAT x, FLOAT y, FLOAT z) {
        v4_ = Vector(4);
#if Q_HAMILTON
        v4_[0] = w;
        v4_[1] = x;
        v4_[2] = y;
        v4_[3] = z;
#else
        v4_[0] = x;
        v4_[1] = y;
        v4_[2] = z;
        v4_[3] = w;
#endif
    }

    Quarternion::Quarternion(const Vector &v4) {
        assert(v4.size() == 4);
        v4_ = v4;
    }

    Matrix Quarternion::rotation_matrix() const {
        Matrix R(3, 3);
#if Q_HAMILTON
        // TODO
#else
        R = (2 * w() * w() - 1) * Matrix::eye(3) - 2 * w() * skew_symmetric(vec()) + 2 * vec() * vec();
        //TODO: Is it necessary to use the approximation equation (Equation (87)) when the rotation angle is small?
#endif
        return R;
    }

    Matrix Quarternion::left_product_matrix() const {
        Matrix L(4,4);
#if Q_HAMILTON
        // TODO
#else
        L(0, 0) =  v4_[3]; L(0, 1) =  v4_[2]; L(0, 2) = -v4_[1]; L(0, 3) =  v4_[0];
        L(1, 0) = -v4_[2]; L(1, 1) =  v4_[3]; L(1, 2) =  v4_[0]; L(1, 3) =  v4_[1];
        L(2, 0) =  v4_[1]; L(2, 1) = -v4_[0]; L(2, 2) =  v4_[3]; L(2, 3) =  v4_[2];
        L(3, 0) = -v4_[0]; L(3, 1) = -v4_[1]; L(3, 2) = -v4_[2]; L(3, 3) =  v4_[3];
#endif
        return L;
    }
}

