#include "my_camera.hpp"

// 构造函数
myCamera::myCamera(unsigned int device_type, int device_index) 
    : handle_(nullptr), is_opened_(false), is_grabbing_(false), 
      device_type_(device_type), device_index_(device_index) {
    
    // 枚举设备
    MV_CC_DEVICE_INFO_LIST device_list;
    int ret = MV_CC_EnumDevices(device_type_, &device_list);
    if (ret != MV_OK) 
        return;
    
    if (device_list.nDeviceNum == 0 || device_index_ >= device_list.nDeviceNum) 
        return;
    
    // 创建设备句柄
    ret = MV_CC_CreateHandle(&handle_, device_list.pDeviceInfo[device_index_]);
    if (ret != MV_OK) 
        return;
    
    // 打开设备
    ret = MV_CC_OpenDevice(handle_);
    if (ret != MV_OK) 
    {
        MV_CC_DestroyHandle(handle_);
        handle_ = nullptr;
        return;
    }
    
    is_opened_ = true;
    
    // 设置相机参数
    set_camera_parameters_();
    
    // 开始采集
    ret = MV_CC_StartGrabbing(handle_);
    if (ret != MV_OK) 
    {
        MV_CC_CloseDevice(handle_);
        MV_CC_DestroyHandle(handle_);
        handle_ = nullptr;
        is_opened_ = false;
        return;
    }
    
    is_grabbing_ = true;
}

// 析构函数
myCamera::~myCamera() {
    if (is_grabbing_) 
        MV_CC_StopGrabbing(handle_);
    
    if (is_opened_) 
        MV_CC_CloseDevice(handle_);
    
    if (handle_ != nullptr) 
        MV_CC_DestroyHandle(handle_);
}

// 读取一帧图像
bool myCamera::read(cv::Mat& frame, unsigned int timeout_ms) {
    if (!is_opened_ || !is_grabbing_) 
        return false;
    
    MV_FRAME_OUT raw;
    int ret = MV_CC_GetImageBuffer(handle_, &raw, timeout_ms);
    if (ret != MV_OK) 
        return false;

    
    // 转换图像格式
    frame = transfer_(raw);
    
    // 释放图像缓冲区
    MV_CC_FreeImageBuffer(handle_, &raw);
    
    return !frame.empty();
}

// 转换图像格式
cv::Mat myCamera::transfer_(MV_FRAME_OUT& raw)
{
    MV_CC_PIXEL_CONVERT_PARAM cvt_param;
    cv::Mat img(cv::Size(raw.stFrameInfo.nWidth, raw.stFrameInfo.nHeight), CV_8U, raw.pBufAddr);

    cvt_param.nWidth = raw.stFrameInfo.nWidth;
    cvt_param.nHeight = raw.stFrameInfo.nHeight;

    cvt_param.pSrcData = raw.pBufAddr;
    cvt_param.nSrcDataLen = raw.stFrameInfo.nFrameLen;
    cvt_param.enSrcPixelType = raw.stFrameInfo.enPixelType;

    cvt_param.pDstBuffer = img.data;
    cvt_param.nDstBufferSize = img.total() * img.elemSize();
    cvt_param.enDstPixelType = PixelType_Gvsp_BGR8_Packed;

    auto pixel_type = raw.stFrameInfo.enPixelType;
    const static std::unordered_map<MvGvspPixelType, cv::ColorConversionCodes> type_map = {
      {PixelType_Gvsp_BayerGR8, cv::COLOR_BayerGR2RGB},
      {PixelType_Gvsp_BayerRG8, cv::COLOR_BayerRG2RGB},
      {PixelType_Gvsp_BayerGB8, cv::COLOR_BayerGB2RGB},
      {PixelType_Gvsp_BayerBG8, cv::COLOR_BayerBG2RGB}};
    cv::cvtColor(img, img, type_map.at(pixel_type));
    
    return img;
}

// 设置相机参数
void myCamera::set_camera_parameters_() {
    if (!is_opened_) return;
    
    MV_CC_SetEnumValue(handle_, "BalanceWhiteAuto", MV_BALANCEWHITE_AUTO_CONTINUOUS);
    MV_CC_SetEnumValue(handle_, "ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);
    MV_CC_SetEnumValue(handle_, "GainAuto", MV_GAIN_MODE_OFF);
    MV_CC_SetFloatValue(handle_, "ExposureTime", 10000);
    MV_CC_SetFloatValue(handle_, "Gain", 20);
    MV_CC_SetFrameRate(handle_, 60);
}