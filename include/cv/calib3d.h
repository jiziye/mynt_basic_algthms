//
// Created by cg on 10/17/19.
//

#ifndef MSCKF_VIO_MYNT_CALIB3D_H
#define MSCKF_VIO_MYNT_CALIB3D_H

#include <vector>

#include "cv/types.h"
#include "maths/vector.h"
#include "maths/mat.h"

namespace mynt {

    /**
     * @brief cv::convertPointsToHomogeneous + cv::projectPoints
     * @param pts_in
     * @param pts_out
     * @param rvec
     * @param tvec
     * @param camera_matrix
     * @param distortion_coeffs
     */
    void project_points(
            const std::vector<mynt::Point2f> &pts_in, std::vector<mynt::Point2f> &pts_out,
            const mynt::Vector3 &rvec, const mynt::Vector3 &tvec,
            const mynt::Mat3 &camera_matrix,
            const mynt::Vector4 &distortion_coeffs);
}

#endif //MSCKF_VIO_MYNT_CALIB3D_H
