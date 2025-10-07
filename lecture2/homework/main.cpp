#include "tools.hpp"

int main(int argc, char** argv) 
{
    // 检查命令行参数
    if (argc != 2) 
    {
        fmt::print("使用方法: {} <图片路径>\n", argv[0]);
        fmt::print("示例: {} image.jpg\n", argv[0]);
        return -1;
    }
    
    // 读取图像
    cv::Mat image = cv::imread(argv[1]);
    
    // 检查图像是否成功加载
    if (image.empty()) 
    {
        fmt::print("无法加载图像: {}\n", argv[1]);
        return -1;
    }
    fmt::print("成功加载图像: {}\n", argv[1]);
    
    // 缩放填充图像到640x640
    cv::Mat result = resizeImageToSquare(image, 640);
    
    // 显示原始图像和结果
    cv::imshow("原始图像", image);
    cv::imshow("缩放结果 (640x640)", result);
    
    fmt::print("按任意键退出...\n");
    
    // 等待按键
    cv::waitKey(0);
    
    return 0;
}