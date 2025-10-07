#include "tools.hpp"

cv::Mat resizeImageToSquare(const cv::Mat& inputImage, int targetSize)
 {
    // 创建目标画布
    cv::Mat outputImage = cv::Mat::zeros(targetSize, targetSize, inputImage.type());
    
    // 获取原始图像尺寸
    int originalWidth = inputImage.cols;
    int originalHeight = inputImage.rows;
    
    fmt::print("原始图像尺寸: {} x {}\n", originalWidth, originalHeight);
    
    // 计算缩放比例
    double scale = std::min(static_cast<double>(targetSize) / originalWidth, 
                           static_cast<double>(targetSize) / originalHeight);
    
    // 计算缩放后的尺寸
    int newWidth = static_cast<int>(originalWidth * scale);
    int newHeight = static_cast<int>(originalHeight * scale);
    
    fmt::print("缩放后尺寸: {} x {}\n", newWidth, newHeight);
    fmt::print("缩放比例: {:.6f}\n", scale);
    
    // 缩放图像
    cv::Mat resizedImage;
    cv::resize(inputImage, resizedImage, cv::Size(newWidth, newHeight), 0, 0, cv::INTER_LINEAR);
    
    // 计算在画布中的位置（居中放置）
    int x = (targetSize - newWidth) / 2;
    int y = (targetSize - newHeight) / 2;
    
    fmt::print("在画布中的位置: ({}, {})\n", x, y);
    
    // 将缩放后的图像复制到画布中央
    cv::Mat roi = outputImage(cv::Rect(x, y, newWidth, newHeight));
    resizedImage.copyTo(roi);
    
    return outputImage;
}