//
// Created by cg on 10/17/19.
//

#include "cv/undistort.h"

#include <limits>

namespace mynt {

    void undistort_points(
            const std::vector<mynt::Point2f> &pts_in, std::vector<mynt::Point2f> &pts_out,
            const mynt::Mat3 &camera_matrix,
            const mynt::Vector4 &distortion_coeffs,
            const mynt::Mat3 &R,
            const mynt::Mat3 &P) {

        FLOAT fx = camera_matrix(0, 0);
        FLOAT fy = camera_matrix(1, 1);
        FLOAT cx = camera_matrix(0, 2);
        FLOAT cy = camera_matrix(1, 2);

        double ifx = 1. / fx;
        double ify = 1. / fy;

        FLOAT k1 = distortion_coeffs[0];
        FLOAT k2 = distortion_coeffs[1];
        FLOAT p1 = distortion_coeffs[2];
        FLOAT p2 = distortion_coeffs[3];

        mynt::Mat3 RR = P * R;

        pts_out.resize(pts_in.size());

        for (int i = 0; i < pts_in.size(); i++) {
            double x, y, x0 = 0, y0 = 0, u, v;
            const mynt::Point2f &pt_in = pts_in[i];
            mynt::Point2f &pt_out = pts_out[i];

            x = (pt_in.x - cx) * ifx;
            y = (pt_in.y - cy) * ify;

            if (true) {
                // compensate tilt distortion
                x0 = x;
                y0 = y;

                // compensate distortion iteratively
                for (int j = 0;; j++) {
                    int max_count = 5;
                    if (j >= max_count)
                        break;
                    double r2 = x * x + y * y;
                    double icdist = 1 / (1 + (k2 * r2 + k1) * r2);
                    double deltaX = 2 * p1 * x * y + p2 * (r2 + 2 * x * x);
                    double deltaY = p1 * (r2 + 2 * y * y) + 2 * p2 * x * y;
                    x = (x0 - deltaX) * icdist;
                    y = (y0 - deltaY) * icdist;
                }
            }

            double xx = RR(0, 0) * x + RR(0, 1) * y + RR(0, 2);
            double yy = RR(1, 0) * x + RR(1, 1) * y + RR(1, 2);
            double ww = 1. / (RR(2, 0) * x + RR(2, 1) * y + RR(2, 2));
            x = xx * ww;
            y = yy * ww;

            pt_out.x = x;
            pt_out.y = y;
        }
    }
}