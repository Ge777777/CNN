// #pragma once

// #include <opencv2/opencv.hpp>
// #include <read_csv.h>
// #include <vector>

// class RGBtoGrayConverter
// {
// public:
//     explicit RGBtoGrayConverter(std::string path) ;
//     cv::Mat get_img();
//     cv::Mat get_gray_img();
//     void show_img();
//     void show_gray_img();
//     void save_gray_img(std::string path);
//     void set_img(cv::Mat img);
//     void set_path(std::string path);
//     void set_lable(int lable);
//     std::string get_path();
//     std::vector<IOData> load_data();
// private:
//     std::string path;
//     cv::Mat img;
//     cv::Mat gray_img;
//     IOData data;

// };