#include "io/my_camera.hpp"
#include "tasks/yolo.hpp"
#include "opencv2/opencv.hpp"
#include "tools/img_tools.hpp"
int main() {
    // 1. 初始化相机
    myCamera camera;
    
    // 2. 初始化YOLO检测器
    std::string config_path = "configs/yolo.yaml";
    auto_aim::YOLO yolo_detector(config_path, true);
    
    int frame_count = 0;
    
    while (true) 
    {
        // 读取一帧图像
        cv::Mat frame;
        if (!camera.read(frame)) 
            break;
        
        // 使用YOLO检测装甲板
        std::list<auto_aim::Armor> armors = yolo_detector.detect(frame, frame_count);
        // 在图像上绘制检测结果
        cv::Mat result_frame = frame.clone();
        for (const auto& armor : armors) 
        {
            // 获取四个关键点（左上、左下、右下、右上）
            std::vector<cv::Point2f> points=armor.points;
            // 使用draw_points函数绘制红色闭合矩形
            tools::draw_points(result_frame, points, cv::Scalar(0, 0, 255), 3);
            
            // 添加标签信息
            std::string color_str = auto_aim::COLORS[static_cast<int>(armor.color)];
            std::string type_str = auto_aim::ARMOR_TYPES[static_cast<int>(armor.type)];
            std::string name_str = auto_aim::ARMOR_NAMES[static_cast<int>(armor.name)];
            std::string label = color_str + " " + name_str + " " + type_str;
            cv::putText(result_frame, label, points[0], 
                       cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);

        }
        // 显示结果
        cv::imshow("Armor Detection - Result", result_frame);
        frame_count++;
        int key = cv::waitKey(1);
        if (key == 27) 
            break;
    }
    
    cv::destroyAllWindows();
    
    return 0;
}