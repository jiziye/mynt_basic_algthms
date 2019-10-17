//
// Created by cg on 10/17/19.
//

#ifndef MSCKF_VIO_MYNT_UNDISTORT_H
#define MSCKF_VIO_MYNT_UNDISTORT_H

#include "cv/types.h"
#include "maths/vector.h"
#include "maths/mat.h"

namespace mynt {

    /**
     * @brief same with cv::undistortPoints, Computes the ideal point coordinates from the observed point coordinates
     * @param pts_in
     * @param pts_out
     * @param camera_matrix
     * @param distortion_coeffs
     * @param R
     * @param P
     */
    void undistort_points(
            const std::vector<mynt::Point2f> &pts_in, std::vector<mynt::Point2f> &pts_out,
            const mynt::Mat3 &camera_matrix,
            const mynt::Vector4 &distortion_coeffs,
            const mynt::Mat3 &R=mynt::Matrix::eye(3),
            const mynt::Mat3 &P=mynt::Matrix::eye(3));
}

#endif //MSCKF_VIO_MYNT_UNDISTORT_H
