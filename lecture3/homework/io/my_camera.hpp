#ifndef MY_CAMERA_HPP
#define MY_CAMERA_HPP

#include "hikrobot/include/MvCameraControl.h"
#include "opencv2/opencv.hpp"
class myCamera {
public:
    /*
     构造函数
     device_type 设备类型，默认USB设备
     device_index 设备索引，默认0
     */
    myCamera(unsigned int device_type = MV_USB_DEVICE, int device_index = 0);
    
    /*
     析构函数
     */
    ~myCamera();
    
    /*
     读取一帧图像
     frame 输出的图像帧
     timeout_ms 超时时间，默认100ms
     成功读取返回true，否则返回false
     */
    bool read(cv::Mat& frame, unsigned int timeout_ms = 100);

private:
    void* handle_;                          // 相机句柄
    bool is_opened_;                        // 相机是否打开
    bool is_grabbing_;                      // 是否正在采集
    unsigned int device_type_;              // 设备类型
    int device_index_;                      // 设备索引
    
    // 禁用拷贝构造和赋值操作
    myCamera(const myCamera&) = delete;
    myCamera& operator=(const myCamera&) = delete;
    
    /*
     转换图像格式
     raw 原始图像数据
     转换后的cv::Mat图像
     */
    cv::Mat transfer_(MV_FRAME_OUT& raw);
    
    /*
     设置相机参数
     */
    void set_camera_parameters_();
};

#endif // MY_CAMERA_HPP