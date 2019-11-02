//
// Created by cg on 9/16/19.
//

#include <gtest/gtest.h>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "cv/types.h"
#include "cv/yimg.h"
#include "cv/corner_detector.h"
#include "cv/image_filtering.h"

TEST(cv, Size)
{
    mynt::Size sz = mynt::Size();
    std::cout << "sz: " << sz << std::endl;

    mynt::Size sza = mynt::Size(100,200);
    mynt::Size szb = mynt::Size(200,300);
    mynt::Size szc = sza + szb;
    std::cout << "szc: " << szc << ", area: " << szc.area() << std::endl;
}

TEST(cv, Point2D)
{
    mynt::Point2i p;
    std::cout<< "p: " << p <<std::endl;
   
    const int n=2; 
    mynt::Point2f a(100,100);
    mynt::Point2f b(200,200);
    mynt::Point2f c = a * n;
    c = 3 * a;
    c = -c;
    std::cout<<a<<"*"<<n<<" = "<<c<<std::endl;

    mynt::Point2f d = a + b;
    std::cout<<a<<"+"<<b<<" = "<<d<<std::endl;

    cv::Vec3d pt1(1,1,1);
    cv::Vec3d pt2(2,2,2);
    double val = (pt1.t() * pt2)[0];
    std::cout << "pt: " << pt1.t() * pt2 << std::endl;
}

TEST(YImg, copy)
{
    cv::Mat mat_src = cv::imread("../data/lena.bmp", cv::ImreadModes::IMREAD_GRAYSCALE);

    ASSERT_FALSE(mat_src.empty());

    mynt::YImg8 yimg_src(mat_src.rows, mat_src.cols);
    memcpy(yimg_src.data(), mat_src.data, yimg_src.size().area());

    mynt::YImg8 yimg_dst(yimg_src.size());
    yimg_src.copy(yimg_dst);

    cv::Mat mat_dst;
    mat_dst.create(mat_src.rows, mat_src.cols, CV_8UC1);
    mempcpy(mat_dst.data, yimg_dst.data(), yimg_dst.size().area());

    cv::imshow("YImg copy test", mat_dst);
    cv::waitKey(1000);
}

TEST(CornerDetector, detect_features)
{
    cv::Mat mat_src = cv::imread("../data/lena.bmp", cv::ImreadModes::IMREAD_GRAYSCALE);

    std::vector<mynt::Point2f> new_features;
    std::vector<double> nm_scores;
    mynt::CornerDetector detector;
    detector.detect_features(mat_src, new_features, nm_scores);

    cv::Mat mat_dst(mat_src.rows, mat_src.cols, CV_8UC3);
    cv::cvtColor(mat_src, mat_dst, CV_GRAY2BGR);
    for (const auto &pt : new_features) {
        cv::circle(mat_dst, cv::Point2f(pt.x, pt.y), 3, cv::Scalar(0, 255, 0), -1);
    }
    cv::imshow("CornerDetector FAST", mat_dst);
    cv::waitKey(1000);
}


TEST(ImageFiltering, gaussian_blur) {
    cv::Mat mat_src = cv::imread("../data/lena.bmp", cv::ImreadModes::IMREAD_GRAYSCALE);

    ASSERT_FALSE(mat_src.empty());

    mynt::YImg8 yimg_src(mat_src.rows, mat_src.cols);
    memcpy(yimg_src.data(), mat_src.data, yimg_src.size().area());

    mynt::YImg8 yimg_dst(yimg_src.size());
    mynt::gaussian_blur(yimg_src, yimg_dst, 5, 0.84089642);

    cv::Mat mat_dst_01;
    mat_dst_01.create(mat_src.rows, mat_src.cols, CV_8UC1);
    mempcpy(mat_dst_01.data, yimg_dst.data(), yimg_dst.size().area());

    cv::Mat mat_dst_02;
    cv::GaussianBlur(mat_src, mat_dst_02, cv::Size(5, 5), 0.84089642);

    mynt::pyr_down(yimg_src, yimg_dst);
    cv::Mat mat_dst_03(yimg_dst.rows(), yimg_dst.cols(), CV_8UC1);
    mempcpy(mat_dst_03.data, yimg_dst.data(), yimg_dst.size().area());

    cv::imshow("GaussianBlur YImg", mat_dst_01);
    cv::imshow("GaussianBlur OCV", mat_dst_02);
    cv::imshow("PyrDown YImg", mat_dst_03);
    cv::waitKey(0);
}
