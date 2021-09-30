#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include<pybind11/pybind11.h>
#include<pybind11/numpy.h>
#include<pybind11/stl.h>
#include"mat_warper.h"

namespace py = pybind11;

py::array_t<unsigned char> test_rgb_to_gray(py::array_t<unsigned char>& input) {

    cv::Mat img_rgb = numpy_uint8_3c_to_cv_mat(input);
    cv::Mat dst;
    cv::cvtColor(img_rgb, dst, cv::COLOR_RGB2GRAY);
    return cv_mat_uint8_1c_to_numpy(dst);

}

py::array_t<unsigned char> test_gray_canny(py::array_t<unsigned char>& input) {
    cv::Mat src = numpy_uint8_1c_to_cv_mat(input);
    cv::Mat dst;
    cv::Canny(src, dst, 30, 60);
    return cv_mat_uint8_1c_to_numpy(dst);
}


/*
@return Python list
*/
py::list test_pyramid_image(py::array_t<unsigned char>& input) {
    cv::Mat src = numpy_uint8_1c_to_cv_mat(input);
    std::vector<cv::Mat> dst;

    cv::buildPyramid(src, dst, 4);

    py::list out;
    for (int i = 0; i < dst.size(); i++)
    {
        out.append<py::array_t<unsigned char>>(cv_mat_uint8_1c_to_numpy(dst.at(i)));
    }
    
    return out;
}

PYBIND11_MODULE(cv_demo1, m) {
    
    m.doc() = "Simple opencv demo";

    m.def("test_rgb_to_gray", &test_rgb_to_gray);
    m.def("test_gray_canny", &test_gray_canny);
    m.def("test_pyramid_image", &test_pyramid_image);

}
