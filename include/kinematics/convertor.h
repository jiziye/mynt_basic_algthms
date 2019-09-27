//
// Created by cg on 9/27/19.
//

#ifndef MSCKF_VIO_MYNT_CONVERTOR_H
#define MSCKF_VIO_MYNT_CONVERTOR_H

#include "kinematics/rotation_matrix.h"

namespace mynt {

    /**
     * @brief Converts a rotation vector to a rotation matrix
     *        ref: https://docs.opencv.org/2.4/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html#rodrigues
     * @param v3
     * @return
     */
    RotationMatrix rodrigues(const Vector3 &v3);
}

#endif //MSCKF_VIO_MYNT_CONVERTOR_H
