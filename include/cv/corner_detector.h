//
// Created by cg on 10/24/19.
//

#ifndef MSCKF_VIO_MYNT_CORNER_DETECTOR_H
#define MSCKF_VIO_MYNT_CORNER_DETECTOR_H

#include <fast/fast.h>

#include "cv/types.h"
#include "cv/yimg.h"

namespace mynt {

    class CornerDetector {
    public:
        CornerDetector(int n_rows = 8, int n_cols = 10, double fast_threshold = 20, double detection_threshold = 40.0);

        ~CornerDetector() {};

        void detect_features(const mynt::YImg8 &image, std::vector<mynt::Point2f> &features, std::vector<double> &nm_scores);

        void set_grid_position(const mynt::Point2f &pos);

        void set_grid_size(int n_rows, int n_cols);

        int get_n_rows() { return grid_n_rows_; }

        int get_n_cols() { return grid_n_cols_; }

        float shiTomasiScore(const mynt::YImg8 &img, int u, int v);

        int sub2ind(const mynt::Point2f &sub);

    private:
        void zero_occupancy_grid();

        std::vector<bool> occupancy_grid_;
        // Size of each grid rectangle in pixels
        int grid_n_rows_, grid_n_cols_, grid_width_, grid_height_;
        // Threshold for corner score
        double detection_threshold_;
        double fast_threshold_;
    }; // CornerDetector class
}

#endif //MSCKF_VIO_MYNT_CORNER_DETECTOR_H
