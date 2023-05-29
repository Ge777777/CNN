// #include "convert_to_grayscale.h"

// RGBtoGrayConverter::RGBtoGrayConverter(std::string path) : data(in_x, in_y, in_z, out_x, out_y, out_z)
// {
//     this->path = std::move(path);
// }

// cv::Mat RGBtoGrayConverter::get_img()
// {
//     return this->img;
// }

// cv::Mat RGBtoGrayConverter::get_gray_img()
// {
//     return this->gray_img;
// }


// void RGBtoGrayConverter::save_gray_img(std::string path)
// {
//     cv::imwrite(path, this->gray_img);
// }

// void RGBtoGrayConverter::set_img(cv::Mat img)
// {
//     this->img = img;
// }

// void RGBtoGrayConverter::set_path(std::string path)
// {
//     this->path = std::move(path);
// }

// std::string RGBtoGrayConverter::get_path()
// {
//     return this->path;
// }

// void RGBtoGrayConverter::show_img()
// {
//     cv::imshow("Image", this->img);
//     cv::waitKey(0);
// }

// void RGBtoGrayConverter::show_gray_img()
// {
//     cv::imshow("Resized Image", this->gray_img);
//     cv::waitKey(0);
// }
// void RGBtoGrayConverter::set_lable(int lable){
//     for (int i = 0; i <= 9; i++){
//         if (i == lable){
//             data.outputVector[i] = 0;
//             }
//         else{
//             data.outputVector[lable] = 1;
//         }
//     }
// }
// std::vector<IOData> RGBtoGrayConverter::load_data() {
//     if(this->img.empty()){
//         std::cout <<"Image is empty!" << std::endl;
//         exit(1);
//     }
//     cv::cvtColor(this->img, this->gray_img, cv::COLOR_BGR2GRAY);
//     cv::resize(this->gray_img, this->gray_img, cv::Size(28, 28));
//     for(int i = 0; i < 28; i++){
//         for(int j = 0; j < 28; j++){
//              data.grayPixels(i, j, 0) = this->gray_img.at<uchar>(i, j);
//         }
//         std::cout << std::endl;
//     }

// }