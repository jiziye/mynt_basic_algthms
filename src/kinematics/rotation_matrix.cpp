//
// Created by cg on 9/21/19.
//

#include "kinematics/rotation_matrix.h"

#include <cmath>
#include <assert.h>

namespace mynt {

    RotationMatrix::RotationMatrix() : Matrix(Matrix::eye(3)) {}

    RotationMatrix::RotationMatrix(const Matrix &mat) : Matrix(mat) {
        // TODO: det == 1, RRT == I
        assert(mat.m == 3 && mat.n == 3);
    }

    RotationMatrix RotationMatrix::rot_mat_x(const FLOAT &angle) {
        FLOAT s = sin(angle);
        FLOAT c = cos(angle);
        Matrix R(3, 3);
        R(0, 0) = +1;
        R(1, 1) = +c;
        R(1, 2) = -s;
        R(2, 1) = +s;
        R(2, 2) = +c;
        return R;
    }

    RotationMatrix RotationMatrix::rot_mat_y(const FLOAT &angle) {
        FLOAT s = sin(angle);
        FLOAT c = cos(angle);
        Matrix R(3, 3);
        R(0, 0) = +c;
        R(0, 2) = +s;
        R(1, 1) = +1;
        R(2, 0) = -s;
        R(2, 2) = +c;
        return R;
    }

    RotationMatrix RotationMatrix::rot_mat_z(const FLOAT &angle) {
        FLOAT s = sin(angle);
        FLOAT c = cos(angle);
        Matrix R(3, 3);
        R(0, 0) = +c;
        R(0, 1) = -s;
        R(1, 0) = +s;
        R(1, 1) = +c;
        R(2, 2) = +1;
        return R;
    }

    const Quarternion RotationMatrix::quarternion() const {
        Quarternion q;
#if Q_HAMILTON
        // TODO
#else
        RotationMatrix R = *this;
        Vector<4> score;
        score[0] = R(0, 0);
        score[1] = R(1, 1);
        score[2] = R(2, 2);
        score[3] = R.trace();

        int max_row = 0;
        score.max_coeff(max_row);

        if (max_row == 0) {
            q[0] = std::sqrt(1 + 2 * R(0, 0) - R.trace()) / 2.0;
            q[1] = (R(0, 1) + R(1, 0)) / (4 * q[0]);
            q[2] = (R(0, 2) + R(2, 0)) / (4 * q[0]);
            q[3] = (R(1, 2) - R(2, 1)) / (4 * q[0]);
        } else if (max_row == 1) {
            q[1] = std::sqrt(1 + 2 * R(1, 1) - R.trace()) / 2.0;
            q[0] = (R(0, 1) + R(1, 0)) / (4 * q[1]);
            q[2] = (R(1, 2) + R(2, 1)) / (4 * q[1]);
            q[3] = (R(2, 0) - R(0, 2)) / (4 * q[1]);
        } else if (max_row == 2) {
            q[2] = std::sqrt(1 + 2 * R(2, 2) - R.trace()) / 2.0;
            q[0] = (R(0, 2) + R(2, 0)) / (4 * q[2]);
            q[1] = (R(1, 2) + R(2, 1)) / (4 * q[2]);
            q[3] = (R(0, 1) - R(1, 0)) / (4 * q[2]);
        } else {
            q[3] = std::sqrt(1 + R.trace()) / 2.0;
            q[0] = (R(1, 2) - R(2, 1)) / (4 * q[3]);
            q[1] = (R(2, 0) - R(0, 2)) / (4 * q[3]);
            q[2] = (R(0, 1) - R(1, 0)) / (4 * q[3]);
        }

        if (q[3] < 0)
            q = -q;
        q.normalized();
#endif
        return q;
    }

    const AngleAxis RotationMatrix::angle_axis() const {
        FLOAT angle = std::acos( (this->trace() - 1) * 0.5 );
        FLOAT s = std::sin(angle);
        RotationMatrix R = (Matrix(*this) - Matrix(*this).transpose()) * 0.5;
        Matrix v3_skew = R / s;
        Vector3 v3;
        v3[0] = -v3_skew(1,2);
        v3[1] =  v3_skew(0,2);
        v3[2] = -v3_skew(0,1);
        return AngleAxis(angle, v3);
    }
}
