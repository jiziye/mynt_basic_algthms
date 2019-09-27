//
// Created by cg on 9/27/19.
//

#include "kinematics/convertor.h"

namespace mynt {

    RotationMatrix rodrigues(const Vector3 &v3) {
        FLOAT theta = v3.l2norm();
        if(theta == 0)
            return RotationMatrix();
        Vector3 v3_hat = v3 / theta;
        RotationMatrix I;
        FLOAT c1 = std::cos(theta);
        FLOAT s1 = std::sin(theta);
        Matrix v3_skew = mynt::skew_symmetric(v3_hat);
        RotationMatrix R = c1 * I + (1-c1) * v3_hat * v3_hat.transpose() + s1 * v3_skew;
        return R;
    }
}
