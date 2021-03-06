//
// Created by cg on 9/16/19.
//

#ifndef MYNT_BASIC_ALGTHMS_ROTATION_MATRIX_H
#define MYNT_BASIC_ALGTHMS_ROTATION_MATRIX_H

#include "kinematics/quarternion.h"

namespace mynt {

    class RotationMatrix : public Matrix {
    public:
        RotationMatrix();

        RotationMatrix(const Matrix &mat);

        inline const FLOAT trace() const {
            FLOAT tr = 0.0;
            for(int i=0; i<3; ++i)
                tr += (*this)(i, i);
            return tr;
        }

        // create 3x3 rotation matrices (convention: http://en.wikipedia.org/wiki/Rotation_matrix)
        static RotationMatrix rot_mat_x(const FLOAT &angle);

        static RotationMatrix rot_mat_y(const FLOAT &angle);

        static RotationMatrix rot_mat_z(const FLOAT &angle);

        /**
         * @brief Convert a rotation matrix to a quaternion.
         * @note Pay attention to the convention used. The function follows the conversion in
         *       "Indirect Kalman Filter for 3D Attitude Estimation: A Tutorial for Quaternion Algebra", Equation (98-99).
         * @return
         */
        const Quarternion quarternion() const;
    };
}

#endif //MYNT_BASIC_ALGTHMS_ROTATION_MATRIX_H
