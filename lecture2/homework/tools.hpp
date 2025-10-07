#ifndef HOMEWORK_TOOLS_HPP
#define HOMEWORK_TOOLS_HPP

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fmt/format.h>

// ====== 函数声明 ======
cv::Mat resizeImageToSquare(const cv::Mat& inputImage, int targetSize = 640);

#endif // HOMEWORK_TOOLS_HPP