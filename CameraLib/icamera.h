#ifndef ICAMERA_H
#define ICAMERA_H

#include <atomic>
#include <string>
#include <memory>
#include <functional>

#include "error_info.h"

enum class ImageType
{
    Unknown = 0,
    JPG,
    JPEG,
    BMP,
};

class Image
{
public:
    void load(const std::string &filename, ImageType = ImageType::Unknown);
    void save(const std::string &filename, ImageType = ImageType::Unknown);
    int height();
    int width();

};

enum class CameraType
{
    AutoDetect = 0,
    USBCamera,
    RTSPCamera,
    VideoFile,
    ImageFile,
};

using PictureHandler = std::function<void (std::shared_ptr<Image>, CameraError)>;

namespace cv {
class VideoCapture;
class Mat;
}


class ICamera
{
public:
    virtual bool is_open() const;
    virtual void open(CameraError &e) noexcept;
    virtual void close(CameraError &e) noexcept;
    // 曝光
    virtual double expose(double exposure, CameraError &ec) noexcept;
    virtual double expose() const;
    // 帧率
    virtual void fps(int f);
    virtual int fps() const;
    virtual double current_fps() const;
    // 拍摄一张图片，同步等待返回，如果打开了异步模式，则获取当前最新的图片，立即返回
    virtual Image take_picture();
    virtual void enable_async_take_picture(bool e);
    // 注册异步回调，每获得一张图片则会调用此函数
    // 回调函数签名 void (std::shared_ptr<Image>, CameraError)
    void async_picture_handler(PictureHandler handler);
    virtual void start_video(const std::string &filename);
    virtual void end_video();
private:
    std::shared_ptr<cv::VideoCapture> _video_ptr;
    std::string _camera_name;
    std::atomic<bool> _is_open;
    std::shared_ptr<cv::Mat> _mat_ptr;
    std::atomic<bool> _enable_async;

private:
    ICamera(std::shared_ptr<cv::VideoCapture> ptr);
    ICamera(const std::string &camera_name);
    friend class CameraInfo;
};

#endif // ICAMERA_H
